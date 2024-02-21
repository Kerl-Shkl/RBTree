#include "IRBTree.h"

// std::shared_ptr<Node> IRBTree::minimumDesc(std::shared_ptr<Node> x) const
// {
//     while (x->left != nullptr) {
//         x = x->left;
//     }
//     return x;
// }

std::shared_ptr<Node> IRBTree::minimumDesc(std::shared_ptr<Node> x)
{
    while (x->left != nullptr) {
        x = x->left;
    }
    return x;
}

std::shared_ptr<Node> IRBTree::maximumDesc(std::shared_ptr<Node> x)
{
    while (x->right != nullptr) {
        x = x->right;
    }
    return x;
}

bool IRBTree::isLeftDesc(const std::shared_ptr<Node>& x) const
{
    auto parent = x->parent.lock();
    return parent->left == x;
}

bool IRBTree::isRightDesc(const std::shared_ptr<Node>& x) const
{
    return !isLeftDesc(x);
}

bool IRBTree::isRed(const std::shared_ptr<Node>& x) const
{
    return x ? x->color == NodeColor::red : false;
}

bool IRBTree::isBlack(const std::shared_ptr<Node>& x) const
{
    return !isRed(x);
}
