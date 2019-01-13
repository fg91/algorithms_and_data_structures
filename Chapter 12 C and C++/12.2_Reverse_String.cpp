// "Copyright 2019 <Fabio M. Graetz>"
#include <iostream>

using std::cout;
using std::endl;

void reverseString(char *word) {
  if (word) {
    char *right = word;
    while (*right) {  // we dont have size information. Find end of char array
      right++;
    }
    right--;  // char array is terminated by null. Take one step back to get last char
    
    char tmp;
    while (word < right) {
      tmp = *word;
      *word++ = *right;
      *right-- = tmp;
    }
  }
}

int main() {
  char word[] = "Fabio";

  reverseString(word);
  cout << word << endl;

  return 0;
}
