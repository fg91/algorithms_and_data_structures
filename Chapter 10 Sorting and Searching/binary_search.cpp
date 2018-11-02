// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

bool binarySearchRec(const vector<int> &vec, int x, int left, int right) {
  // Base case
  if (left > right) return false;

  // If you wish to prevent int overflow, do mid = left + ((right - left) / 2);
  int mid = (left + right) / 2;
  if (vec[mid] == x) {
    return true;
  } else if (vec[mid] < x) {
    return binarySearchRec(vec, x, mid + 1, right);
  } else {
    return binarySearchRec(vec, x, left, mid - 1);
  }
}

bool binarySearchIter(const vector<int> &vec, int x) {
  int left = 0;
  int right = vec.size() - 1;

  while (left <= right) {
    int mid = (left + right) / 2;
    if (x == vec[mid]) {
      return true;
    } else if (x < vec[mid]) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return false;
}

int main() {
  int searchFor = 50;
  vector<int> vec{1, 2, 3, 5, 13, 20, 25, 50, 62, 78, 90};

  cout << binarySearchRec(vec, searchFor, 0, vec.size() - 1) << endl;
  cout << binarySearchIter(vec, searchFor) << endl;
  
  return 0;
}
