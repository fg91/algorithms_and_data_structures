// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::map;

bool stringToBool(string s) {
  return s == "1";
}

int countEval(string s, bool result, map<string, int> *memo) {
  // Base cases
  if (s.size() == 0) return 0;
  if (s.size() == 1) return stringToBool(s) == result ? 1 : 0;
  map<string, int>::iterator it = memo->find(std::to_string(result) + "-" + s);
  if (it != memo->end()) {
    return it->second;
  }

  int ways = 0;
  for (int i = 1; i < s.length(); i += 2) {  // only choose the operators at positions 1, 3, ...
    char c = s.at(i);
    string left = s.substr(0, i);  // exclusive i
    string right = s.substr(i+1);

    // Evaluate both sides for both results
    int leftTrue   = countEval(left, true, memo);
    int leftFalse  = countEval(left, false, memo);
    int rightTrue  = countEval(right, true, memo);
    int rightFalse = countEval(right, false, memo);
    int total = (leftTrue + leftFalse) * (rightTrue + rightFalse);

    int totalTrue = 0;
    if (c == '^') {
      totalTrue = leftTrue * rightFalse + leftFalse * rightTrue;
    } else if (c == '&') {
      totalTrue = leftTrue * rightTrue;
    } else if (c == '|') {
      totalTrue = leftTrue * rightTrue + leftFalse * rightTrue + leftTrue * rightFalse;
    }
    int sub = result ? totalTrue : total - totalTrue;
    ways += sub;
  }
  memo->insert(std::make_pair(std::to_string(result) + "-" + s, ways));
  return ways;
}

int main() {
  map<string, int> memo;
  cout << "Should be 2:\t" << countEval("1^0|0|1", false, &memo) << endl;
  cout << "Should be 10:\t" << countEval("0&0&0&1^1|0", true, &memo) << endl;
  return 0;
}
