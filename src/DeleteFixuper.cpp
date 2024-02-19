#include "DeleteFixuper.h"
#include "RBTree.h"

DeleteFixuper::DeleteFixuper(RBTree& tree)
: tree(tree)
{}

void DeleteFixuper::FixUp(std::shared_ptr<Node> x)
{
    while (x != tree.root && RBTree::isBlack(x)) {
        if (RBTree::isLeftDesc(x)) {
            auto parent = x->parent.lock();
            auto sibling = parent->right;
            if (RBTree::isRed(sibling)) {
                sibling->color = NodeColor::black;
                parent->color = NodeColor::red;
                tree.LeftRotate(parent);
                parent = x->parent.lock();
                sibling = parent->right;
            }
            if (RBTree::isBlack(sibling->left) &&
                RBTree::isBlack(sibling->right))
            {
                sibling->color = NodeColor::red;
                x = parent;
            }
            else {
                if (RBTree::isBlack(sibling->right)) {
                    sibling->left->color = NodeColor::black;
                    sibling->color = NodeColor::red;
                    tree.RightRotate(sibling);
                    parent = x->parent.lock();
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = NodeColor::black;
                sibling->right->color = NodeColor::black;
                tree.LeftRotate(parent);
                x = tree.root;
            }
        }
        else {
            auto parent = x->parent.lock();
            auto sibling = parent->left;
            if (RBTree::isRed(sibling)) {
                sibling->color = NodeColor::black;
                parent->color = NodeColor::red;
                tree.RightRotate(parent);
                parent = x->parent.lock();
                sibling = parent->left;
            }
            if (RBTree::isBlack(sibling->left) &&
                RBTree::isBlack(sibling->right))
            {
                sibling->color = NodeColor::red;
                x = parent;
            }
            else {
                if (RBTree::isBlack(sibling->left)) {
                    sibling->right->color = NodeColor::black;
                    sibling->color = NodeColor::red;
                    tree.LeftRotate(sibling);
                    parent = x->parent.lock();
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = NodeColor::black;
                sibling->left->color = NodeColor::black;
                tree.RightRotate(parent);
                x = tree.root;
            }
        }
    }
    x->color = NodeColor::black;
}
