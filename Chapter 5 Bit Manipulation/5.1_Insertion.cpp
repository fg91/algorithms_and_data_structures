// "Copyright 2018 <Fabio M. Graetz>"
#include <math.h>
#include <iostream>
#include <bitset>
#include <string>

using std::cout;
using std::endl;
using std::bitset;
using std::string;

int insert(int N, int M, int i, int j) {
  // Create mask with 0's from i to j (inclusive)
  // left and right part of the mask
  int allOnes = ~0;
  int left = allOnes << (j + 1);
  int right = (1 << i) - 1;
  int mask = left | right;
  
  // Clear bits j through i using mask and then put M there
  int Ncleared = N & mask;
  int Mshifted = M << i;
  return Ncleared | Mshifted;
}

int main() {
  bitset<16> NN(string("10000000000"));
  bitset<16> MM(string("10011"));

  auto result = insert(static_cast<int>(NN.to_ulong()),
                       static_cast<int>(MM.to_ulong()),
                       2, 6);

  cout << bitset<16>(result) << endl;
  return 0;
}
