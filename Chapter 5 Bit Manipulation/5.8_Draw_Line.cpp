// "Copyright 2018 <Fabio M. Graetz>"

#include <iostream>

using std::cout;
using std::endl;
using std::bitset;

void printScreen(unsigned char* arr, int width, int height) {
  int c = width*height - 1;
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      cout << std::bitset<8>(static_cast<unsigned>(arr[c])) << " "<< std::flush;
      c--;
    }
    cout << endl;
  }
  cout << endl;
}

void drawLine(unsigned char* screen, int width, int height, int x1, int x2, int y) {

  int start_offset = x1 % 8;
  int first_full_byte = x1 / 8;
  if (start_offset != 0) {
    first_full_byte++;
  }

  int end_offset = x2 % 8;
  int last_full_byte = x2 / 8;
  if (end_offset != 7) {
    last_full_byte--;
  }

  // Set full bytes
  if (x1 / 8 != x2 / 8) {
    for (int i = first_full_byte; i <= last_full_byte; i++) {
      screen[i + y * width] = 0xFF;
    }
  }
  // Create masks for start and end of line
  int start_mask = 0xFF << start_offset;
  int end_mask = ~(0xFF << (end_offset + 1));

  // Set start and end of line
  // If x1 and x2 are in the same byte
  if (x1 / 8 == x2 / 8) {
    screen[y * width + x1 / 8] |= (end_mask & start_mask);
  } else {
    if (start_offset != 0) {
      int byte_number = y * width + first_full_byte - 1;
      screen[byte_number] |= start_mask;
    }
    if (end_offset != 7) {
      int byte_number = y * width + last_full_byte + 1;
      screen[byte_number] |= end_mask;
    }
  }
  printScreen(screen, width, height);
}

int main() {

  int width = 4;
  int height = 3;
  unsigned char *screen = new unsigned char[height*width];

  std::fill(screen, screen + height * width, 0);
  drawLine(screen, width, height, 9, 13, 0);
  

  std::fill(screen, screen + height * width, 0);
  drawLine(screen, width, height, 5, 10, 2);

  std::fill(screen, screen + height * width, 0);
  drawLine(screen, width, height, 6, 24, 1);


  delete [] screen;
  
  return 0;
}
