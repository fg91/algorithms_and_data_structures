// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>

using std::cout;
using std::endl;
using std::bitset;

int conversion(int a, int b) {
 
  int count = 0;
  for (int c = a ^ b; c != 0; c >>= 1) {
    count += c & 1;
  }
  return count;
}

int conversion2(int a, int b) {
  int count = 0;
  for (int c = a^b; c != 0; c = c & (c-1)) {
    count++;
  }
  return count;
}

int main() {
  int a = 29;
  int b = 15;

  cout << bitset<32>(a) << endl;
  cout << bitset<32>(b) << endl;
  cout << "Number of bits that have to be flipped: " << conversion2(a, b) << endl;
  return 0;
}
