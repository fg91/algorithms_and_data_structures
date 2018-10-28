// "Copyright 2018 <Fabio M. Graetz>"
#include <math.h>
#include <iostream>
#include <vector>
#include <stack>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;
using std::sort;

// --- Box class --- //

class Box {
 public:
  float w = 0;
  float d = 0;
  float h = 0;
  
 public:
  Box(float w, float d, float h) : w(w), d(d), h(h) {}
  bool operator<(const Box &other) const {
    return w < other.w && d < other.d;
  }
  friend ostream &operator<<(ostream &out, const Box &b) {
    out << "w: " << b.w << "; d: " << b.d <<"; h: " << b.h;
    return out;
  }
};

// --- Solution 1 --- //
int getMaxHeight(vector<Box> *boxes, int bottomIndex, vector<int> *memo) {
  // check if in memo
  if (bottomIndex < boxes->size() && memo->at(bottomIndex) > 0) {
    return memo->at(bottomIndex);
  }

  float maxHeight = 0;

  for (int i = bottomIndex + 1; i < boxes->size(); i++) {
    // if the box is smaller than the bottom box
    if (boxes->at(i) < boxes->at(bottomIndex)) {
      int height = getMaxHeight(boxes, i, memo);
      maxHeight = fmax(height, maxHeight);
    }
  }
  maxHeight += boxes->at(bottomIndex).h;
  
  (*memo)[bottomIndex] = maxHeight;
  return maxHeight;
}

int getMaxHeight(vector<Box> boxes) {
  // sort the boxes regarding width
  sort(boxes.begin(), boxes.end(), [](Box a, Box b) {return a.w > b.w;});
  
  int maxHeight = 0;
  vector<int> memo(boxes.size());

  for (int i = 0; i < boxes.size(); i++) {
    int height = getMaxHeight(&boxes, i, &memo);
    maxHeight = fmax(height, maxHeight);
  }
  return maxHeight;
}

// --- Solution 2 --- //

int getMaxHeight2(vector<Box> *boxes, Box *bottom, int offset, vector<int> *memo) {
  // Base case
  if (offset >= boxes->size()) {
    return 0;
  }

  // height with this bottom
  Box newBottom = boxes->at(offset);
  int heightWithBottom = 0;
  if (bottom == nullptr || newBottom < *bottom) {
    // if not in memo
    if ((*memo)[offset] == 0) {
      (*memo)[offset] = getMaxHeight2(boxes, &newBottom, offset + 1, memo);
      (*memo)[offset] += newBottom.h;
    }
    heightWithBottom = (*memo)[offset];
  }
  // height without this bottom
  int heightWithoutBottom = getMaxHeight2(boxes, bottom, offset + 1, memo);

  // return the larger height
  return fmax(heightWithBottom, heightWithoutBottom);
}


int getMaxHeight2(vector<Box> boxes) {
  // sort the boxes regarding width
  sort(boxes.begin(), boxes.end(), [](Box a, Box b) {return a.w > b.w;});
  vector<int> memo(boxes.size());
  return getMaxHeight2(&boxes, nullptr, 0, &memo);
}

int main() {

  vector<Box> l{Box{3., 3., 3.}, Box(1., 1., 1.), Box{2., 2., 2.}, Box{3, 4, 5}, Box{1.8, 2.2, 3}};
  
  cout << getMaxHeight(l) << endl;
  cout << getMaxHeight2(l) << endl;
  
  return 0;
}
