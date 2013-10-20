#include "bst.h"

#include <iostream>
#include <vector>

using namespace std;

BSTNode *setup() {
  vector<int> values;
  for (int i = 0; i < 10; ++i)
    values.push_back(i);

  return BSTNode::fromVector(values);
}

bool testBSTFromVector() {
  BSTNode *root = setup();
  int height = root->getHeight();
  delete root;

  return height == 4;
}

bool testInorderRecursive() {
  BSTNode *root = setup();

  vector<int> result;
  root->inorderRecursive(result);

  delete root;

  for (size_t i = 0; i < result.size(); ++i)
    if (result[i] != (int) i)
      return false;

  return result.size() == 10;
}

bool testInorderIterative() {
  BSTNode *root = setup();

  vector<int> result = root->inorderIterative();
  delete root;

  for (size_t i = 0; i < result.size(); ++i)
    if (result[i] != (int) i)
      return false;

  return result.size() == 10;
}

int main() {
  cout << (testBSTFromVector() ? "PASSED" : "FAILED") <<
    " : BST conversion from array" << endl;
  cout << (testInorderRecursive() ? "PASSED" : "FAILED") <<
    " : BST inorder recursive traversal" << endl;
  cout << (testInorderIterative() ? "PASSED" : "FAILED") <<
    " : BST inorder iterative traversal" << endl;
  return 0;
}
