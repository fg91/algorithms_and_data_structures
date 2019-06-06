// "Copyright 2019 <Fabio M. Graetz>"
#include <iostream>
#include <memory>
#include <cassert>
using std::cout;
using std::endl;
using std::flush;
using std::shared_ptr;
using std::make_shared;
using std::initializer_list;
using std::ostream;

template<class T>
class Node {
public:
  T value;
  shared_ptr<Node<int>> next;
public:
  explicit Node(T value) : value(value), next(nullptr) {}
  Node(T value, Node &next) : value(value), next(&next) {}
};

template<class T>
class LinkedList {
public:
  shared_ptr<Node<T>> head;
  shared_ptr<Node<T>> tail;
public:
  LinkedList() : head(nullptr), tail(nullptr) {}
  LinkedList(initializer_list<T> ll) {
    for (auto l : ll)
      add(l);
  }
  void add(T value) {
    if (head == nullptr) {
      head = make_shared<Node<T>>(Node<T>(value));
      tail = head;
    } else {
      tail->next = make_shared<Node<T>>(Node<T>(value));
      tail = tail->next;
    }
  }
  void add(initializer_list<T> ll) {
    for (auto l : ll)
      add(l);
  }
  friend ostream &operator<<(ostream & out, const LinkedList<T> &ll) {
    shared_ptr<Node<T>> curr = ll.head;
    while (curr->next != nullptr) {
      out << curr->value << "->" << flush;
      curr = curr->next;
    }
    out << curr->value << flush;
    return out;
  }
};

template<class T>
void reversePart(shared_ptr<Node<T>> node_a, shared_ptr<Node<T>> node_b) {
  auto curr = node_a->next;
  auto prev = node_a;

  while (curr != nullptr && curr != node_b) {
    auto next = curr->next;
    curr->next = prev;

    prev = curr;
    curr = next;
  }
  curr->next = prev;
}

template< class T>
void reversePart(LinkedList<T> &list, T a, T b) {
  /*
    The solution assumes that the linked list contains a node 
    with value a and after that a node with value b.
   */

  assert(a != b);
  using nodePtr = shared_ptr<Node<T>>;
  
  nodePtr node_a = list.head;
  nodePtr before_node_a = nullptr;

  while(node_a != nullptr && node_a->value != a) {
    before_node_a = node_a;
    node_a = node_a->next;
  }

  nodePtr node_b = node_a;

  while(node_b != nullptr && node_b->value != b) {
    node_b = node_b->next;
  }

  nodePtr after_node_b = node_b->next;

  reversePart(node_a, node_b);

  node_a->next = after_node_b;
  if (node_a != list.head) {
    before_node_a->next = node_b;
  } else {
    list.head = node_b;
  }
  
  if (list.tail == node_b) {
    list.tail = node_a;
  }
}

int main() {

  LinkedList<int> test1({2,4,7,5,1,0,9,8,6});
  LinkedList<int> test2({2,4,7,5,1,0,9,8,6});
  LinkedList<int> test3({2,4,7,5,1,0,9,8,6});
  LinkedList<int> test4({2,4,7,5,1,0,9,8,6});
  
  cout << test1 << endl << endl;

  cout << "Reverse from 7 to 5:" << endl;
  reversePart(test1, 7, 5);
  cout << test1 << endl << endl;

  cout << "Reverse from 7 to 8:" << endl;
  reversePart(test2, 7, 8);
  cout << test2 << endl << endl;

  cout << "Reverse from 2 to 7:" << endl;
  reversePart(test3, 2, 7);
  cout << test3 << endl << endl;

  cout << "Reverse from 0 to 6:" << endl;
  reversePart(test4, 0, 6);
  cout << test4 << endl << endl;

  return 0;
}
