#include "IsCorrectRBT.h"
#include "RBTree.h"

static bool isCorrect(const RBTree& tree);

bool isRBTreeCorrect(const RBTree& tree)
{
    return isCorrect(tree);
}

static bool isRootBlack(const RBTree& tree)
{
    return RBTree::isBlack(tree.root);
}

static bool isNodeHasColor(const std::shared_ptr<Node>& node)
{
    return RBTree::isBlack(node) || RBTree::isRed(node);
}

static bool hasRedNodeBlackDescs(const std::shared_ptr<Node>& red_node)
{
    return RBTree::isBlack(red_node->left) && RBTree::isBlack(red_node->right);
}

static bool everyNodeCheck(const std::shared_ptr<Node>& node)
{
    bool result = isNodeHasColor(node);
    if (RBTree::isRed(node)) {
        result = result && hasRedNodeBlackDescs(node);
    }
    return result;
}

static int scanTreeAndCountBL(const std::shared_ptr<Node>& node, bool& ok)
{
    if (node == nullptr) {
        return 0;
    }
    int left = scanTreeAndCountBL(node->left, ok);
    int right = scanTreeAndCountBL(node->right, ok);
    ok = ok && left == right && everyNodeCheck(node);

    int cur = RBTree::isBlack(node) ? 1 : 0;
    return cur + left + right;
}

static bool isCorrect(const RBTree& tree)
{
    bool result = true;
    scanTreeAndCountBL(tree.root, result);
    return result;
}
