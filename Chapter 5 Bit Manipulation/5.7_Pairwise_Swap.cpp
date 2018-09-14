// "Copyright 2018 <Fabio M. Graetz>"

#include <iostream>
using std::cout;
using std::endl;
using std::bitset;

int pairwiseSwap(int num) {

  int maskOdd = 0xaaaaaaaa;
  int maskEven = 0x55555555;

  int odds = num & maskOdd;
  int evens = num & maskEven;
  odds = static_cast<unsigned int>(odds) >> 1;
  evens <<= 1;

  return odds | evens;
}

int main() {

  int num = 9;
  cout << bitset<32>(num) << endl;
  int result = pairwiseSwap(num);
  cout << bitset<32>(result) << endl;
  
  return 0;
}
