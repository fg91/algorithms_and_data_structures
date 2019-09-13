// "Copyright 2019 <Fabio M. Graetz>"
#include <iostream>
#include <memory>
#include <initializer_list>
#include <ostream>

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
  shared_ptr<Node<T>> next;
public:
  explicit Node(T value) : value(value), next(nullptr) {} 
  Node(T value, shared_ptr<Node<T>> &next) : value(value), next(next) {}
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
      head = make_shared<Node<T>>(value);
      tail = head;
    } else {
      tail->next = make_shared<Node<T>>(value);
      tail = tail->next;
    }
  }

  void add(initializer_list<T> ll) {
    for (auto l : ll)
      add(l);
  }

  void reverse() {
    shared_ptr<Node<T>> prev = nullptr;
    shared_ptr<Node<T>> next = nullptr;
    shared_ptr<Node<T>> new_tail = head;
    auto curr = head;

    while(curr != nullptr) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    
    head = prev;
    tail = new_tail;
  }

  friend ostream &operator<<(ostream &out, const LinkedList<T> &ll) {
    shared_ptr<Node<T>> curr = ll.head;

    while(curr != ll.tail) {
      out << curr->value << "->" << flush;
      curr = curr->next;
    }
    out << curr->value << flush;
    return out;
  }
};

int main() {
  LinkedList<float> ll({1., 2., 3., 4., 5.});
  cout << ll << endl;
  ll.reverse();
  cout << ll << endl;

  return 0;
}
