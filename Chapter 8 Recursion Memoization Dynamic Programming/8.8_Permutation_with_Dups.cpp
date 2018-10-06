// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_set;


vector<string> permuation1(string s) {
  vector<string> results;
  if (s.length() == 0) {
    results.push_back("");
  } else {
    unordered_set<char> used;
    for (int i = 0; i < s.length(); i++) {
      if (used.count(s.at(i)) == 0) {
          used.insert(s.at(i));
          string before = s.substr(0, i);
          string after = s.substr(i + 1);
          vector<string> permuations = permuation1(before + after);
          for (string perm : permuations) {
            results.push_back(s.at(i) + perm);
          }
        }
    }
  }
  return results;
}

int main() {
  cout << "Permutations of 'abc'" << endl;
  for (string perm : permuation1("abc")) {
    cout << perm << endl;
  }
  cout << endl;
  cout << "Permutations of 'abb'" << endl;
  for (string perm : permuation1("abb")) {
    cout << perm << endl;
  }
  cout << endl;
  cout << "Permutations of 'bbb'" << endl;
  for (string perm : permuation1("bbb")) {
    cout << perm << endl;
  }

  return 0;
}
