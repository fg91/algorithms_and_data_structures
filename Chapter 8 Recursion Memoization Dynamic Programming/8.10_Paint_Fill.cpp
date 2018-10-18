// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::flush;
using std::vector;

enum Color {r, g, b};

void printImage(vector<vector<Color> > *image) {
  for (vector<vector<Color> >::iterator it = image->begin(); it != image->end(); it++) {
    for (vector<Color>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
      if (*it2 == r) {cout << "r " << flush;}
      if (*it2 == g) {cout << "g " << flush;}
      if (*it2 == b) {cout << "b " << flush;}
    }
    cout << endl;
  }
  cout << endl;
}

bool FillColor(vector<vector<Color> > *image, int row, int col, Color ncolor, Color ocolor) {
  if (row >= image->size() || row < 0 || col >= image[0].size() || col < 0) {
    return false;
  }
  if ((*image)[row][col] == ocolor) {
    (*image)[row][col] = ncolor;
    FillColor(image, row + 1, col, ncolor, ocolor);
    FillColor(image, row - 1, col, ncolor, ocolor);
    FillColor(image, row, col + 1, ncolor, ocolor);
    FillColor(image, row, col - 1, ncolor, ocolor);
  }
  return true;
}

void FillColor(vector<vector<Color> > *image, int row, int col, Color ncolor) {
  FillColor(image, row, col, ncolor, (*image)[row][col]);
}

int main() {
  vector<vector<Color> > image{
    {r, r, r, r},
    {r, r, r, r},
    {g, g, r, r},
    {r, r, g, r}
  };
  
  printImage(&image);
  Color ncolor = b;
  FillColor(&image, 1, 1, b);
  printImage(&image);
  
  return 0;
}
