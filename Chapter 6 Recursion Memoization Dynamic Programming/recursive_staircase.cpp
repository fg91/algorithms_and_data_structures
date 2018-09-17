// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <vector>
#include <cstdint>

using std::cout;
using std::endl;
using std::vector;

// Method 1: Recursion
// Time complexity close to O(3^N)!

int64_t countPathsRec(int steps) {
  if (steps < 0) {
    return 0;
  } else if (steps == 0) {
    return 1;
  }
  return countPathsRec(steps - 1)
      + countPathsRec(steps - 2)
      + countPathsRec(steps - 3);
}

// Method 2: Memoization
// Time complexity O(N), space O(N)

int64_t countPathsMemo(int steps, vector<int64_t> &memo) {
  if (steps < 0) {
    return 0;
  } else if (steps == 0) {
    return 1;
  } else if (memo[steps] == 0) {
    memo[steps] = countPathsMemo(steps - 1, memo)
        + countPathsMemo(steps - 2, memo)
        + countPathsMemo(steps - 3, memo);
    if (memo[steps] < 0) {
      cout << "Negative number detected! Number of steps too large for int64_t!" << endl;
    }
  }
  return memo[steps];
}

int64_t countPathsMemo(int steps) {
  if (steps < 0) {
    return 0;
  }
  const int size = steps;
  vector<int64_t> memo(steps + 1, 0);
  return countPathsMemo(steps, memo);
}

// Method 3: Dynamic Programming
// Time complexity O(N), space O(N)

int64_t countPathsDP(int steps) {
  if (steps < 0) {
    return 0;
  } else if (steps <= 1) {
    return 1;
  }

  vector<int64_t> paths(steps + 1, 0);
  paths[0] = 1;
  paths[1] = 1;
  paths[2] = 2;

  for (int i = 3; i <= steps; i++) {
    paths[i] = paths[i - 1] + paths[i - 2] + paths[i - 3];
    if (paths[i] < 0) {
      return -1;  // Error code
    }
  }
  return paths[steps];
}

// Method 4: Dynamic Programming improved
// Time complexity O(N), space O(1)

int64_t countPathsIterative(int steps) {
  if (steps < 0) {
    return 0;
  } else if (steps <= 1) {
    return 1;
  }

  vector<int64_t> paths{1, 1, 2};

  for (int i = 3; i <= steps; i++) {
    int64_t count = paths[2] + paths[1] + paths[0];
    paths[0] = paths[1];
    paths[1] = paths[2];
    paths[2] = count;
    if (count < 0) {
      return -1;  // Error code
    }
  }
  return paths[2];
}

int main() {

  // Be aware, that the number of steps can become too large for int64_t if totalSteps is too large!
  
  int totalSteps = 50;

  //  cout << countPathsRec(totalSteps) << endl;
  cout << countPathsMemo(totalSteps) << endl;
  cout << countPathsDP(totalSteps) << endl;
  cout << countPathsIterative(totalSteps) << endl;

  return 0;
}
