// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::flush;
using std::swap;

#define SIZE 10

void printArr(int arr[]) {
  for (int i = 0; i < SIZE; i++) {
    cout << arr[i] << "\t" << flush;
  }
  cout << endl;
}

int partition(int arr[], int left, int right, int pivot) {
  while (left <= right) {
    while (arr[left] < pivot) left++;
    while (arr[right] >  pivot) right--;
    if (left <= right) {
      swap(arr[left], arr[right]);
      left++;
      right--;
    }
  }
  return left;
}

void quicksort(int arr[], int left, int right) {
  if (left >= right) {
    return;
  }
  int pivot = arr[(left + right) / 2];

  /*
  cout << "pivot: " << pivot << ", left: " << arr[left] << ", right: " << arr[right] << endl;
  printArr(arr);
  */

  int index = partition(arr, left, right, pivot);

  /*
  printArr(arr);
  cout << "index: " << index << endl << endl;
  */

  // quicksort left and right halves
  quicksort(arr, left, index - 1);
  quicksort(arr, index, right);
}

void quicksort(int arr[]) {
  quicksort(arr, 0, SIZE - 1);
}

int main() {
  int arr[SIZE]{7, 34, 98, 12, 9, 31, 43, 76, 1, 19};
  quicksort(arr);
  
  for (int i = 0; i < SIZE; i++) {
    cout << arr[i] << " " << flush;
  }
  cout << endl;

  return 0;
}

/*
  O(n * log n) average
  O(n^2)       worst case
 */
