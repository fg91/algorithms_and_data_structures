// "Copyright 2019 <Fabio M. Graetz>"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

void printLastKLines(const std::string &fileName, int lines) {
  const int k = lines;
  std::string L[k];
  int size = 0;
  
  std::ifstream in;
  in.open(fileName);
  if (in.is_open()) {
    // read file line by line and store last k line
    while (in.peek() != EOF) {
      getline(in, L[size % k]);
      size++;
    }
    in.close();
  } else {
    throw std::runtime_error("Could not open file");
  }

  // print elements in original order
  int start = size > k ? (size % k) : 0;
  
  for (int i = 0; i < std::min(k, size); i++) {
    cout << L[(start + i) % k] << endl;
  }
}

int main() {
  std::string filename("read_file.txt");
  printLastKLines(filename, 3);
  
  return 0;
}
