#include "bst.h"

#include <algorithm>
#include <limits>
#include <stack>

using namespace std;

BSTNode::~BSTNode() {
  if (m_left)
    delete m_left;
  if (m_right)
    delete m_right;
}

size_t BSTNode::getHeight() {
  size_t subtree_height = 0;
  if (m_left)
    subtree_height = m_left->getHeight();
  if (m_right)
    subtree_height = max(subtree_height, m_right->getHeight());
  return 1 + subtree_height;
}

void BSTNode::inorderRecursive(vector<int>& values) {
  if (m_left)
    m_left->inorderRecursive(values);
  values.push_back(m_value);
  if (m_right)
    m_right->inorderRecursive(values);
}

vector<int> BSTNode::inorderIterative() {
  vector<int> values;

  stack<BSTNode*> nodes;
  nodes.push(this);

  while (!nodes.empty()) {
    BSTNode *crt = nodes.top();
    nodes.pop();

    if (crt->m_expanded) {
      values.push_back(crt->m_value);
      continue;
    }

    if (crt->m_right && !crt->m_right->m_expanded)
      nodes.push(crt->m_right);

    crt->m_expanded = true;
    nodes.push(crt);

    if (crt->m_left && !crt->m_left->m_expanded)
      nodes.push(crt->m_left);
  }

  return values;
}

BSTNode* BSTNode::fromVector(vector<int> values) {
  sort(values.begin(), values.end());
  values.erase(unique(values.begin(), values.end()), values.end());

  return new BSTNode(values, 0, values.size());
}

BSTNode::BSTNode(const vector<int>& sortedUniqueValues,
                 size_t begin, size_t end)
  : m_value(numeric_limits<int>::min())
  , m_expanded(false)
  , m_left(0)
  , m_right(0) {

  size_t mid = (begin + end) / 2;
  m_value = sortedUniqueValues[mid];

  if (end - begin == 1)
    return;

  if (begin != mid)
    m_left = new BSTNode(sortedUniqueValues, begin, mid);
  if (mid + 1 != end)
    m_right = new BSTNode(sortedUniqueValues, mid + 1, end);
}
