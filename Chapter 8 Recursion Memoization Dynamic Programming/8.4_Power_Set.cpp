// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::flush;
using std::vector;

// ----- Solution 1 ----- //
// ----- Recursion ------ //

// Time and space complexity is O(n * 2^n)
// which is total number of elements across all subsets

vector<vector<int> > getSubsets(vector<int> *set, int index) {
  vector<vector<int> > allSubsets;
  if (set->size() == index) {
    allSubsets.push_back(vector<int>());  // Base case - add empty set
  } else {
    allSubsets = getSubsets(set, index + 1);
    int item = set->at(index);
    vector<vector<int> > moreSubsets;
    for (auto subset : allSubsets) {
      vector<int> newSubset(subset);
      newSubset.push_back(item);
      moreSubsets.push_back(newSubset);
    }
    for (auto subset : moreSubsets) {
      allSubsets.push_back(subset);
    }
  }
  return allSubsets;
}

// ----- Solution 2 ----- //
// ----- Iteratively ---- //

vector<int> convertIntToSet(vector<int> *set, int k) {
  vector<int> subset;
  int index = 0;
  for (int i = k; i > 0; i >>= 1, index++) {
    if ((i & 1) == 1) {
      subset.push_back(set->at(index));
    }
  }
  return subset;
}

vector<vector<int> > getSubsetsIter(vector<int> set) {
  vector<vector<int> > allSubsets;
  // There are 2^n subsets
  int max = 1 << set.size();
  for (int k = 0; k < max; k++) {
    vector<int> subset = convertIntToSet(&set, k);
    allSubsets.push_back(subset);
  }
  return allSubsets;
}

int main() {

  vector<int> set {1, 2, 3};
  auto result = getSubsets(&set, 0);
  cout << "Recursive solution" << endl;
  for (auto vec : result) {
    cout << "[" << flush;
    for (int i : vec) {
      cout  << i << "," << flush;
    }
    cout << "]" << endl;
  }
  cout << endl << "Iterative solution" << endl;
  auto result2 = getSubsetsIter(set);
  for (auto vec : result2) {
    cout << "[" << flush;
    for (int i : vec) {
      cout  << i << "," << flush;
    }
    cout << "]" << endl;
  }
  return 0;
}
