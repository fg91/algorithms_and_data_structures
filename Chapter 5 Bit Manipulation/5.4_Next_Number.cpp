// "Copyright 2018 <Fabio M. Graetz>"

#include <math.h>
#include <iostream>

using std::cout;
using std::endl;
using std::bitset;

int getNext(int n) {
  // Compute c0 and c1
  int c = n;
  int c0 = 0;
  int c1 = 0;

  while (((c & 1) == 0) && (c != 0)) {
    c0++;
    c >>= 1;
  }

  while ((c & 1) == 1) {
    c1++;
    c >>= 1;
  }

  // Error: if n="block of 1s" + "block of 0s" there is no bigger number
  // with same number of 1s (this is the case when c0+c1=31)
  if (c0 + c1 == 31 || c0 + c1 == 0) {
    return -1;
  }

  int p = c0 + c1;
  n |= (1 << p);
  n &= ~0 << p;
  n |= (1 << (c1 - 1)) - 1;
  return n;
}

int getNextArithmetic(int n) {
  // Compute c0 and c1
  int c = n;
  int c0 = 0;
  int c1 = 0;

  while (((c & 1) == 0) && (c != 0)) {
    c0++;
    c >>= 1;
  }

  while ((c & 1) == 1) {
    c1++;
    c >>= 1;
  }

  // Error: if n="block of 1s" + "block of 0s" there is no bigger number
  // with same number of 1s (this is the case when c0+c1=31)
  if (c0 + c1 == 31 || c0 + c1 == 0) {
    return -1;
  }

  int p = c0 + c1;

  // n += pow(2, c0) - 1;
  // n += 1;
  // n += pow(2, c1 - 1) - 1;

  return n + pow(2, c0) + pow(2, c1 - 1) - 1;
}

int getPrev(int n) {
  // Compute c0 and c1
  int c = n;
  int c0 = 0;
  int c1 = 0;

  while ((c & 1) == 1) {
    c1++;
    c >>= 1;
  }

  // Error: if n = "block of 0s" + "block of 1s" there is no smaller number
  // with the same number of 1s
  if (c == 0) {
    return -1;
  }
  
  while (((c & 1) == 0) && (c != 0)) {
    c0++;
    c >>= 1;
  }

  int p = c0 + c1;
  n &= ((~0) << (p + 1));
  int mask = (1 << (c1 + 1)) -1;
  n |= mask << (c0 - 1);
  
  
  return n;
}

int getPrevArithmetic(int n) {
  // Compute c0 and c1
  int c = n;
  int c0 = 0;
  int c1 = 0;

  while ((c & 1) == 1) {
    c1++;
    c >>= 1;
  }

  // Error: if n = "block of 0s" + "block of 1s" there is no smaller number
  // with the same number of 1s
  if (c == 0) {
    return -1;
  }
  
  while (((c & 1) == 0) && (c != 0)) {
    c0++;
    c >>= 1;
  }

  int p = c0 + c1;
  
  return n - pow(2, c1)  - pow(2, c0 - 1) + 1;
}
int main() {

  int testNext = 13948;
  int testPrev = 10115;
  cout << "Original\t" << bitset<16>(testNext) << endl;
  cout << "Next\t\t" << bitset<16>(getNext(testNext)) << endl;
  cout << "NextArith\t" << bitset<16>(getNextArithmetic(testNext)) << endl << endl;
  cout << "Original\t" << bitset<16>(testPrev) << endl;
  cout << "Previous\t" << bitset<16>(getPrev(testPrev)) << endl;
  cout << "PreviousArith\t" << bitset<16>(getPrevArithmetic(testPrev)) << endl;
  return 0;
}


