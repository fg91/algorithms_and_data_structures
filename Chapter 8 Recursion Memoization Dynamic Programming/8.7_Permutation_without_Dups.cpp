// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// --- Solution 1 --- //
vector<string> permuation1(string s) {
  vector<string> results;
  if (s.length() == 0) {
    results.push_back("");
  } else {
    for (int i = 0; i < s.length(); i++) {
      string before = s.substr(0, i);
      string after = s.substr(i + 1);
      vector<string> permuations = permuation1(before + after);
      for (string perm : permuations) {
        results.push_back(s.at(i) + perm);
      }
    }
  }
  return results;
}

// --- Solution 2 --- //
void permuation2(string prefix, string remainder, vector<string> &results) {
  if (remainder.length() == 0) {
    results.push_back(prefix);
  }
  for (int i = 0; i < remainder.length(); i++) {
    permuation2(prefix + remainder.at(i), remainder.substr(0, i)
                + remainder.substr(i + 1), results);
  }
}

vector<string> permuation2(string s) {
  vector<string> results;
  permuation2("", s, results);
  return results;
}

int main() {
  string test = "abc";
  for (string perm : permuation1(test)) {
    cout << perm << endl;
  }
  cout << endl;
  for (string perm : permuation2(test)) {
    cout << perm << endl;
  }
  return 0;
}
