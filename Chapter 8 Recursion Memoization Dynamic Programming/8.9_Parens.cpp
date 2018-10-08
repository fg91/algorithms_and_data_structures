// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::unordered_set;
using std::vector;

// --- Solution 1 --- //
// inefficient because it creates many duplicates
// that are discarded by the hashmap

string insertAt(string str, int leftIndex) {
  string left = str.substr(0, leftIndex + 1);
  string right = str.substr(leftIndex + 1);
  return left + "()" + right;
}

unordered_set<string> parens(int n) {
  unordered_set<string> results;
  if (n == 0) {
    results.insert("");
  } else {
    auto prev = parens(n - 1);
    for (string s : prev) {
      for (int i = 0; i < s.length(); i++) {
        if (s.at(i) == '(') {
          results.insert(insertAt(s, i));
        }
      }
      results.insert("()" + s);
    }
  }
  return results;
}

// --- Solution 2 --- //

void addParens(vector<string> *results, int leftRem,
               int rightRem, string str, int index) {
  if (leftRem < 0 || rightRem < leftRem) return;  // invalid case
  if (leftRem == 0 && rightRem == 0) {
    results->push_back(str);
  } else {
    str[index] = '(';
    addParens(results, leftRem - 1, rightRem, str, index + 1);
    str[index] = ')';
    addParens(results, leftRem, rightRem - 1, str, index + 1);
  }
}

vector<string> generateParens(int n) {
  vector<string> results;
  addParens(&results, n, n, string(2 * n, ' '), 0);
  return results;
}

int main() {
  int i = 1;
  int count = 4;
  for (string s : parens(count)) {
    cout << i++ << "\t" <<s << endl;
  }
  cout << endl;
  i = 1;
  for (string s : generateParens(count)) {
    cout << i++ << "\t" <<s << endl;
  }

  return 0;
}
