#ifndef TESTS_RBTREE_INCLUDE_TESTRBTREE_H
#define TESTS_RBTREE_INCLUDE_TESTRBTREE_H

#include "RBTreeRefactor.h"

class TestRBTree : public RBTreeRefactor
{
public:
    using RBTreeRefactor::getRoot;
    using RBTreeRefactor::LeftRotate;
    using RBTreeRefactor::RightRotate;

    bool IsTreeCorrect() const
    {
        bool result = isRootBlack();
        scanTreeAndCountBlack(getRoot(), result);
        return result;
    }

private:
    bool isRootBlack() const
    {
        return isBlack(getRoot());
    }

    bool isNodeHasColor(const std::shared_ptr<Node>& node) const
    {
        return isBlack(node) || isRed(node);
    }

    bool hasRedNodeBlackDescs(const std::shared_ptr<Node>& red_node) const
    {
        return isBlack(red_node->left) && isBlack(red_node->right);
    }

    bool areDescsInOrder(const std::shared_ptr<Node>& node) const
    {
        bool result = true;
        if (node->right != nullptr) {
            result = result && node->right->value >= node->value;
        }
        if (node->left != nullptr) {
            result = result && node->left->value < node->value;
        }
        return result;
    }

    bool everyNodeCheck(const std::shared_ptr<Node>& node) const
    {
        bool result = isNodeHasColor(node);
        if (isRed(node)) {
            result = result && hasRedNodeBlackDescs(node);
        }
        if (node != nullptr) {
            result = result && areDescsInOrder(node);
        }
        return result;
    }

    int scanTreeAndCountBlack(const std::shared_ptr<Node>& node, bool& ok) const
    {
        if (!ok || node == nullptr) {
            return 0;
        }
        int left = scanTreeAndCountBlack(node->left, ok);
        int right = scanTreeAndCountBlack(node->right, ok);
        ok = ok && left == right && everyNodeCheck(node);

        int cur = isBlack(node) ? 1 : 0;
        return cur + left;
    }
};

#endif  // end of include guard: TESTS_RBTREE_INCLUDE_TESTRBTREE_H
