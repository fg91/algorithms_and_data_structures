// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// ----- Very simple solution ----- //
// Not very space efficient though
int multiply(const int a, const int b) {
  int arr[a][b];
  return sizeof(arr)/sizeof(int);
}

// ----- Solution 1 ----- //
// ----- Memoization ---- //

int minProductMemoHelper(int smaller, int bigger, vector<int> *memo) {
  if (smaller == 0) return 0;
  else if (smaller == 1) return bigger;
  else if (memo->at(smaller) > 0) return memo->at(smaller);
  
  int half = smaller >> 1;
  int side1 = minProductMemoHelper(half, bigger, memo);
  int side2 = side1;

  if (smaller % 2 == 1) {
    side2 = minProductMemoHelper(smaller - half, bigger, memo);
  }
  memo->operator[](smaller) = side1+ side2;
  return memo->at(smaller);
}

int minProductMemo(int a, int b) {
  int bigger = a > b ? a : b;
  int smaller = a > b ? b : a;
  
  vector<int> memo(smaller + 1, 0);
  return minProductMemoHelper(smaller, bigger, &memo);
}

// ----- Solution 2 ----- //
// Recurses straight down, always halfing smaller
// This gives a time complexity of O(log(smaller))

int minProductHelper(int smaller, int bigger) {
  if (smaller == 0) return 0;
  if (smaller == 1) return bigger;

  int half = smaller >> 1;
  int side1 = minProductHelper(half, bigger);

  int side2 = ((smaller % 2) == 0) ? side1 : side1 + bigger;
  return side1 + side2;
}

int minProduct(int a, int b) {
  int bigger = a > b ? a : b;
  int smaller = a > b ? b : a;
  return minProductHelper(smaller, bigger);
}

int main() {

  cout << multiply(17, 23) << endl;
  cout << minProduct(17, 23) << endl;
  cout << minProductMemo(17, 23) << endl;
  
  return 0;
}
