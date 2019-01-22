// "Copyright 2019 <Faibio M. Graetz>"
#include <iostream>
#include <map>

using std::cout;
using std::endl;
using std::map;

struct Node {
  int value;
  Node * left = nullptr;
  Node * right = nullptr;

  explicit Node(int v) : value(v) {}
};

Node * CopyNodeRecursive(Node * current, map<Node*, Node*> *nodeMap) {
  if (current == nullptr) {
    return nullptr;
  }

  // check if we already where here
  map<Node*, Node*>::iterator it = nodeMap->find(current);
  if (it != nodeMap->end()) {
    return it->second;
  }

  // we did not visit this node before
  Node * node = new Node(current->value);
  nodeMap->insert(std::make_pair(current, node));
  node->left = CopyNodeRecursive(current->left, nodeMap);
  node->right = CopyNodeRecursive(current->right, nodeMap);

  return node;
}

std::pair<Node *, map<Node*, Node*>> CopyNode(Node * node) {
  map<Node*, Node*> nodeMap;
  return std::make_pair(CopyNodeRecursive(node, &nodeMap), nodeMap);
}

int main() {

  // Let's quickly test this:
  Node root(0);
  Node left(1);
  Node right(2);
  Node rightright(3);

  root.left = &left;
  root.right = &right;
  right.right = &rightright;
  rightright.left = &left;

  auto copiedGraph = CopyNode(&root);
  Node * copy = copiedGraph.first;
  cout << copy->right->right->left->value << endl;

  // Free up memory:
  map<Node*, Node*> nodes = copiedGraph.second;
  for (auto l : nodes) {
    delete l.second;
  }
  
  return 0;
}

/*
  Be careful:
  The solution in "Cracking the coding interview" does address the obvious memory leak!
  Compile with g++ -g -o <name> -std=c++11 <file_name> to check for memory leaks with
  valgrind --leak-check=yes ./<name>
*/
