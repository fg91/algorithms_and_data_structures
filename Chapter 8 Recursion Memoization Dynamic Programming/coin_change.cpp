// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;

// Method 1: Recursion

int64_t makeChange(const vector<int> &coins, int money, int index) {
  // Base cases
  if (money == 0) {
    return 1;
  }
  if (index >= coins.size()) {
    return 0;
  }

  int amountWithCoin = 0;
  int64_t  ways = 0;
  
  while (amountWithCoin <= money) {
    int remaining = money - amountWithCoin;
    ways += makeChange(coins, remaining, index + 1);
    amountWithCoin += coins[index];
  }
  return ways;
}

int64_t makeChange(const vector<int> &coins, int money) {
  return makeChange(coins, money, 0);
}

// Method 2: Memoization

int64_t makeChangeMemo(const vector<int> &coins,
                       int money, int index,
                       map<string, int64_t> *memo) {
  // Base cases
  if (money == 0) {
    return 1;
  }
  if (index >= coins.size()) {
    return 0;
  }
  // Make sure that the key contains a separation!
  // Otherwise 12 + 1 cannot be distinguished from 1 + 21
  string key = std::to_string(money) + "-" + std::to_string(index);
  int amountWithCoin = 0;
  int64_t  ways = 0;

  auto it = memo->find(key);
  if (it != memo->end()) {
    return memo->at(key);
  } else {
    while (amountWithCoin <= money) {
      int remaining = money - amountWithCoin;
      ways += makeChangeMemo(coins, remaining, index + 1, memo);
      amountWithCoin += coins[index];
    }
  }
  memo->insert(make_pair(key, ways));
  return ways;
}

int64_t makeChangeMemo(const vector<int> &coins, int money) {
  map<string, int64_t> memo;
  return makeChangeMemo(coins, money, 0, &memo);
}

int main() {
  const vector<int> coins({50, 25, 10, 5, 2, 1});
  
  cout << makeChange(coins, 200) << endl;
  cout << makeChangeMemo(coins, 200) << endl;
  
  return 0;
}




