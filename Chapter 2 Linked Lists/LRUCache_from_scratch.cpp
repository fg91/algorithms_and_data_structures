// "Copyright 2019 <Fabio M. Graetz>"
#include <iostream>
#include <map>

using std::cout;
using std::endl;


template<class T>
struct Node {
  Node * prevNode;
  Node * nextNode;

  T value;
  int key;

  Node(int k, T val, Node * p, Node * n) :
      prevNode(p), nextNode(n), value(val), key(k) {}

  Node(int k, T val) :
      prevNode(nullptr), nextNode(nullptr), value(val), key(k) {}
};

template<class T>
class Cache {
 protected:
  int capacity;
  std::map<int, Node<T>*> mapKeyToNode;
  Node<T> * head;  // double linked list head
  Node<T> * tail;
  virtual void set(int, T) = 0;
  virtual T get(int) = 0;
};

template<class T>
class LRUCache : public Cache<T> {
 protected:
  int capacity;
  std::map<int, Node<T>*> mapKeyToNode;
  Node<T> * head;
  Node<T> * tail;

 public:
  class iterator;

 public:
  explicit LRUCache(int c) : capacity(c) {
    head = nullptr;
    tail = nullptr;
    mapKeyToNode = {};
  }

  ~LRUCache() {
    for (typename std::map<int, Node<T>*>::iterator it = mapKeyToNode.begin(); it != mapKeyToNode.end(); it++) {
      delete it->second;
    }
  }

  int size() {
    return mapKeyToNode.size();
  }

  iterator begin() {
    return iterator(head->value, *this);
  }

  iterator end() {
    return iterator(-1, *this);
  }

  virtual void set(int key, T val) {
    typename std::map<int, Node<T>*>::iterator it = mapKeyToNode.find(key);

    // Case 1: not contained yet
    if (it == mapKeyToNode.end()) {
      Node<T> * node = new Node<T>(key, val);
      mapKeyToNode[key] = node;
      // Subcase 1.1: there is still space in the cache
      if (capacity > 0) {
        capacity--;
        // If the linked list is still empty, the new node is head and tail
        if (head == nullptr) {
          head = node;
          tail = node;
        } else {  // otherwise insert node at front of linked list
          node->nextNode = head;
          head->prevNode = node;
          head = node;
        }
      } else {  // Subcase 1.2: there is no more space in cache, replace tail
        node->nextNode = head;
        head->prevNode = node;
        head = node;

        // Remove tail;
        Node<T> * tmp = tail;
        tail = tail->prevNode;
        tail->nextNode = nullptr;
        mapKeyToNode.erase(tmp->key);
        delete tmp;
      }
    } else {  // Case 2: already contained
      Node<T> * tmp = it->second;
      // Subcase 2.1: node is head, simply update value
      if (tmp == head) {
        head->value = val;
      } else {  // Subcase 2.2: node is not head
        if (tmp == tail) {  // Subcase 2.2.1: node is tail
          tail = tmp->prevNode;
          tail->nextNode = nullptr;
          tmp->prevNode = nullptr;
          tmp->nextNode = head;
          head->prevNode = tmp;
          head = tmp;
        } else {  // Subcase 2.2: node is somewhere in the middle
          tmp->prevNode->nextNode = tmp->nextNode;
          tmp->nextNode->prevNode = tmp->prevNode;
          tmp->nextNode = head;
          tmp->prevNode = nullptr;
          head->prevNode = tmp;
          head = tmp;
        }
      }
    }
  }

  virtual T get(int key) {
    typename std::map<int, Node<T>*>::iterator it = mapKeyToNode.find(key);

    if (it == mapKeyToNode.end()) {
      return -1;
    } else {
      return mapKeyToNode[key]->value;
    }
  }

  int getNext(int key) {
    if (key != tail->key) {
      return mapKeyToNode[key]->nextNode->key;
    } else {
      return -1;
    }
  }

  void print() {
    Node<T> * runner = head;
    while (true) {
      cout << runner->value << " " << std::flush;
      if (runner == tail) {
        break;
      }
      runner = runner->nextNode;
    }
    cout << endl;
  }
};

template<class T>
class LRUCache<T>::iterator {
 private:
  int m_key;
  LRUCache & m_cache;
 public:
  iterator(int key, LRUCache &c) : m_key(key), m_cache(c) {}

  iterator &operator++() {
    m_key = m_cache.getNext(m_key);
    return *this;
  }

  iterator &operator++(int) {
    m_key = m_cache.getNext(m_key);
    return *this;
  }

  T operator*() {
    return m_cache.get(m_key);
  }

  bool operator!=(const iterator &other) const {
    return m_key != other.m_key;
  }
};



int main() {
  LRUCache<double> cache(3);
  cache.set(1,1.1);
  cache.set(2,2.2);
  cache.set(3,3.3);
  cache.set(4,4.4);
  cache.set(2,2.2);
  cache.set(3,3.3);
  cache.set(0,0.0);

  cache.print();

  for (LRUCache<double>::iterator it = cache.begin(); it != cache.end(); it++) {
    cout << *it << " " << std::flush;
  }
  cout << endl;
  
  return 0;
}
