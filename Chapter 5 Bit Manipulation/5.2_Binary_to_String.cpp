// "Copyright <Fabio M. Graetz>"
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>

using std::cout;
using std::endl;
using std::bitset;
using std::stringstream;
using std::string;

string printBinary(double num) {
  if (num >=1 || num <= 0) {
    return "ERROR";
  }

  stringstream ss;
  ss << ".";
  double frac = 0.5;
  
  while (num > 0) {
    if (ss.str().length() > 32) {
      return "ERROR";
    }
    if (num >= frac) {
      ss << "1";
      num -= frac;
    } else {
      ss << "0";
    }
    frac /= 2.;
  }
  return ss.str();
}

int main() {

  cout << "Test case 1\t" << 0.41015625 << endl;
  cout << "Real solution is\t" << ".01101001" << endl;
  cout << "Result of code is \t" << printBinary(0.41015625) << endl;
  
  return 0;
}
