// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <bitset>

using std::cout;
using std::endl;
using std::bitset;

bool getBit(int num, int i) {
  return (((1 << i) & num) != 0);
}

int setBit(int num, int i) {
  return num | (1 << i);
}

int clearBit(int num, int i) {
  int mask = ~(1 << i);
  return num & mask;
}

int clearBitsMSBthroughI(int num, int i) {
  int mask = (1 << i) - 1;
  return mask & num;
}

int clearBitsIthrough0(int num, int i) {
  int mask = (-1 << (i + 1));
  return num & mask;
}

int updateBit(int num, int i, bool bitIs1) {
  int mask = ~(1 << i);
  int val = bitIs1 == true ? 1 : 0;
  return (num & mask) | (val << i);
}

int main() {

  int a = 8;
  cout << bitset<4>(a) << "\t" << getBit(a, 3) << endl;


  int b = 3;
  cout << bitset<4>(b) << "\t" << bitset<4>(setBit(b, 3)) << endl;

  int c = 5;
  cout << bitset<4>(c) << "\t" << bitset<4>(clearBit(c, 2)) << endl;

  int d = 7;
  cout << bitset<4>(d) << "\t" << bitset<4>(clearBitsMSBthroughI(d, 2)) << endl;

  int e = 234;
  cout << bitset<8>(e) << "\t" << bitset<8>(clearBitsIthrough0(e, 3)) << endl;

  int f = 234;
  cout << bitset<8>(f) << "\t" << bitset<8>(updateBit(f, 7, false)) << endl;
  
  return 0;
}
