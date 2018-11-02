// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>

using std::cout;
using std::endl;
using std::swap;
using std::flush;

void printArr(int arr[], const int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << "\t" << flush;
  }
  cout << endl;
}

void bubblesort(int arr[], const int size) {
  bool isSorted = false;
  int lastUnsorted = size - 1;
  while (!isSorted) {
    isSorted = true;
    for (int i = 0; i < lastUnsorted; i++) {
      if (arr[i] > arr[i + 1]) {
        swap(arr[i], arr[i + 1]);
        isSorted = false;
      }
    }
    printArr(arr, size);
    lastUnsorted--;
  }
}

int main() {
  const int size = 10;
  int arr[size]{7, 34, 98, 12, 9, 31, 43, 76, 1, 19};

  bubblesort(arr, size);

  return 0;
}

// bubble sort is pretty slow: in the worst case we have to do n passes through the array
// each of which takes a time of n giving us O(n^2)
// O(1) space
// Small optimization: After the first pass, the last element will be the largest.
// In the second pass, you don't have to check this again. After the second pass
// the second last element will be in the right spot as well, ...
