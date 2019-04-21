// "Copyright 2019 <Fabio M. Graetz>"
#include <iostream>
#include <vector>

using namespace std;

template<
  class T,
  class Container = vector<T>,
  class Compare = std::less<typename Container::value_type>
  >
class Heap {
 private:
  Container items;
  Compare comp;

 private:
  size_t getLeftChildIdx(size_t parentIdx) {
    return 2 * parentIdx + 1;
  }

  size_t getRightChildIdx(size_t parentIdx) {
    return 2 * parentIdx + 2;
  }

  int getParentIdx(size_t childIdx) {
    return (childIdx - 1) / 2;
  }

  bool hasLeftChild(size_t parentIdx) {
    return getLeftChildIdx(parentIdx) < items.size();
  }

  bool hasRightChild(size_t parentIdx) {
    return getRightChildIdx(parentIdx) < items.size();
  }

  bool hasParent(size_t childIdx) {
    return getParentIdx(childIdx) >= 0;
  }

  void heapifyDown() {
    int idx = 0;
    while (hasLeftChild(idx)) {
      int smallerChildIdx = getLeftChildIdx(idx);
      if (hasRightChild(idx) && comp(items[getRightChildIdx(idx)] ,items[getLeftChildIdx(idx)])) {
	smallerChildIdx = getRightChildIdx(idx);
      }
      if (comp(items[idx] ,items[smallerChildIdx])) {
	break;
      } else {
	swap(items[idx], items[smallerChildIdx]);
	idx = smallerChildIdx;
      }
    }
  }

  void heapifyUp() {
    int idx = items.size() - 1;

    while (hasParent(idx) && comp(items[idx], items[getParentIdx(idx)])) {
      swap(items[idx], items[getParentIdx(idx)]);
      idx = getParentIdx(idx);
    }
  }

 public:
  T &peek() {
    if (items.size() == 0) {
      throw "Heap is empty";
    }
    return items[0];
  }

  T pop() {
    if (items.size() == 0) {
      throw "Heap is empty";
    }
    T item = items[0];
    items[0] = items[items.size() - 1];
    items.pop_back();
    heapifyDown();
    return item;
  }

  void push(T val) {
    items.push_back(val);
    heapifyUp();
  }

  void print() {
    for (T i : items)
      cout << i << " " << flush;

    cout << endl;
  }

  bool empty() {
    return items.size() == 0;
  }
};

int main()
{
  //Heap<int, vector<int>, greater<int>> pq;
  Heap<int> pq;
  try {
    pq.peek();
  } catch (const char* e) {
    cout << e << endl;
  }

  for (int i : {4, 1, 0, 5, 7, 2, 3}) {
    pq.push(i);
  }
  
  while(!pq.empty())
    cout << pq.pop() << endl;

  return 0;
}
