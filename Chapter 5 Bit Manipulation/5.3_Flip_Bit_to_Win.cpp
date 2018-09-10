// "Copyright 2018 <Fabio M. Graetz>"

#include <math.h>
#include <iostream>
#include <bitset>

using std::cout;
using std:: endl;
using std::bitset;

int flipBit(int num) {
  // Runtime is O(b) where b is number of bits, space is O(1)
  if (~num == 0) {
    return sizeof(int) * 8;
  }
  
  int currentLength = 0;
  int prevLength = 0;
  int maxLength = 1;

  while (num != 0) {
    if ((num & 1) == 1) {  // If current bit is 1
      currentLength++;
    } else if ((num & 1) == 0) {  // If current bit is 0

      // Solution presented in the book is more complicated than necessary:
      // prevLength = (num & 2) == 0 ? 0 : currentLength;
      // currentLength = 0;

      // Instead use:
      prevLength = currentLength;
      currentLength = 0;
    }
    maxLength = fmax(prevLength + currentLength + 1, maxLength);
    num = static_cast<unsigned int>(num) >> 1;
  }
  return maxLength;
}

int main() {
  // Let's test the algorithm:
  int num = 124513469;
  cout << bitset<32>(num) << endl;
  cout << flipBit(num) << endl;
  return 0;
}
