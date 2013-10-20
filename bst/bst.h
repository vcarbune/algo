/**
 * Binary Search Tree implementation.
 */

#ifndef BST_H

#include <vector>

class BSTNode {
  public:
    ~BSTNode();

    std::size_t getHeight();
    void inorderRecursive(std::vector<int>&);
    std::vector<int> inorderIterative();

    static BSTNode* fromVector(std::vector<int>);

  private:
    BSTNode(const std::vector<int>&, std::size_t, std::size_t);
    int m_value;
    bool m_expanded;

    BSTNode *m_left;
    BSTNode *m_right;
};

#endif // BST_H
