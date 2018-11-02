// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::swap;
using std::flush;

#define SIZE 10

void printArr(int arr[], const int size) {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << "\t" << flush;
  }
  cout << endl;
}

void mergeHalves(int arr[], int buffer[], int leftStart, int rightEnd) {
  int middle = (leftStart + rightEnd) / 2;
  int leftEnd = middle;
  int rightStart = middle + 1;

  // go through both halves and merge them together
  int left = leftStart;
  int right = rightStart;
  int index = leftStart;

  while (left <= leftEnd && right <= rightEnd) {
    if (arr[left] <= arr[right]) {
      buffer[index] = arr[left];
      left++;
    } else {
      buffer[index] = arr[right];
      right++;
    }
    index++;
  }
  // at this point either left or right hit their respective end
  // so only one of the following two lines has an effect
  // copy the remaining entries into buffer
  // + 1 because exclusive upper bound
  std::copy(arr + left, arr + leftEnd + 1, buffer + index);
  std::copy(arr + right, arr + rightEnd + 1, buffer + index);

  // copy the buffer to arr
  std::copy(buffer + leftStart, buffer + rightEnd + 1, arr + leftStart);
  }

void mergesort(int arr[], int buffer[], int left, int right) {
  // Base case
  if (left >= right) {
    return;
  }

  // sorting left and right half
  int middle = (left + right) / 2;
  mergesort(arr, buffer, left, middle);
  mergesort(arr, buffer, middle + 1, right);

  // merge the left and right half
  mergeHalves(arr, buffer, left, right);
}

void mergesort(int arr[]) {
  int buffer[SIZE];
  mergesort(arr, buffer, 0, SIZE - 1);
}

int main() {
  int arr[SIZE]{7, 34, 98, 12, 9, 31, 43, 76, 1, 19};
  mergesort(arr);
  
  for (int i = 0; i < SIZE; i++) {
    cout << arr[i] << " " << flush;
  }
  cout << endl;

  return 0;
}

/*
  - time: pretty efficient, always O(n * log n)
  - space: O(n)

  1. mergesort (array's left half)
  2. mergesort (array's right half)
  3. merge left & right half in sorted order
 */
