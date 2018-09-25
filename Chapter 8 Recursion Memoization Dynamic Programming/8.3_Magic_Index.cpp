// "Copyright 2018 <Fabio M. Graetz>"
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

// ---------- Distinct integers in array --------- //

int magicIndex(int arr[], int left, int right) {
  if (left > right) {
    return -1;
  }
  int middle = (left + right) / 2;
  if (arr[middle] == middle) {
    return middle;
  } else if (arr[middle] < middle) {
    return magicIndex(arr, middle + 1, right);
  } else {
    return magicIndex(arr, left, middle - 1);
  }
}

int magicIndex(int arr[], int size) {
  return magicIndex(arr, 0, size - 1);
}

// ------------------ Follow up ----------------- //
// ------- Non distinct integers in array -------- //
int magicIndexFollowUp(int arr[], int left, int right) {
  if (left > right) {
    return -1;
  }
  int middle = (left + right) / 2;
  if (arr[middle] == middle) {
    return middle;
  }
  /* Left side */
  int leftIndex = fmin(middle - 1, arr[middle]);
  int resultLeft = magicIndexFollowUp(arr, left, leftIndex);
  if (resultLeft >= 0) {
    return resultLeft;
  }

  /* Right side */
  int rightIndex = fmax(middle + 1, arr[middle]);
  int resultRight = magicIndexFollowUp(arr, rightIndex, right);
  return resultRight;
}

int magicIndexFollowUp(int arr[], int size) {
  return magicIndexFollowUp(arr, 0, size - 1);
}


int main() {
  const int size = 11;
  int arr[size] = {-40, -20, -1, 1, 2, 3, 5, 7, 9, 12, 13};

  cout << "Distinct integers in array: " << magicIndex(arr, size) << endl;

  int arr2[size] = {-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13};

  cout << "Follow up, non distinct integers in array: " << magicIndexFollowUp(arr2, size) << endl;
  
  return 0;
}
