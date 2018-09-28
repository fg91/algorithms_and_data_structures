// "Copyright 2018 <Fabio M. Graetz>"
#include <iostream>
#include <stack>

using std::cout;
using std::flush;
using std::endl;
using std::stack;
using std::ostream;

class Tower {
 private:
  stack<int> disks;
  int index;

 public:
  Tower() {}
  explicit Tower(int index) : index(index) {
  }
  int getIndex() const {
    return index;
  }
  void add(int d) {
    if (!disks.empty() && disks.top() <= d) {
      cout << "Could not place disk " << d << endl;
    } else {
      disks.push(d);
    }
  }
  void moveTopToTower(Tower *t) {
    int top = disks.top();
    t->add(top);
    disks.pop();
  }
  void moveDisks(int n, Tower *destination, Tower *buffer) {
    if (n > 0) {
      moveDisks(n - 1, buffer, destination);
      moveTopToTower(destination);
      buffer->moveDisks(n - 1, destination, this);
    }
  }
  friend ostream &operator<<(ostream &out, const Tower &tower) {
    stack<int> dummy(tower.disks);
    out << tower.getIndex() << ":\t" << flush;
    while (!dummy.empty()) {
      out << dummy.top() << " " << flush;
      dummy.pop();
    }
    return out;
  }
};

int main() {
  const int n = 3;
  int nDisks = 4;

  // Initialize the towers
  Tower *towers = new Tower[n];
  for (int i = 0; i < n; i++) {
    towers[i] = Tower(i);
  }

  // Fill the left tower with disks
  for (int i = nDisks - 1; i >= 0; i--) {
    towers[0].add(i);
  }
  cout << towers[0] << endl;
  cout << towers[1] << endl;
  cout << towers[2] << endl;

  // Solve the game
  towers[0].moveDisks(nDisks, &towers[2], &towers[1]);
  cout << endl;

  cout << towers[0] << endl;
  cout << towers[1] << endl;
  cout << towers[2] << endl;
      
  delete [] towers;
  return 0;
}
