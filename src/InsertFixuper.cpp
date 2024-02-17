#include "InsertFixuper.h"
#include "RBTree.h"

InsertFixuper::InsertFixuper(RBTree& rbtree)
: tree(rbtree)
{}

void InsertFixuper::FixUp(std::shared_ptr<Node> z)
{
    while (RBTree::isRed(z->parent.lock())) {
        auto parent = z->parent.lock();
        auto grandpa = parent->parent.lock();
        if (RBTree::isLeftDesc(parent)) {
            auto uncle = grandpa->right;
            if (RBTree::isRed(uncle)) {
                parent->color = NodeColor::black;
                uncle->color = NodeColor::black;
                grandpa->color = NodeColor::black;
                z = grandpa;
            }
            else {
                if (RBTree::isRightDesc(z)) {
                    z = parent;
                    tree.LeftRotate(z);
                    parent = z->parent.lock();
                    grandpa = parent->parent.lock();
                }
                parent->color = NodeColor::black;
                grandpa->color = NodeColor::red;
            }
        }
        else {
            auto uncle = grandpa->left;
            if (RBTree::isRed(uncle)) {
                parent->color = NodeColor::black;
                uncle->color = NodeColor::black;
                grandpa->color = NodeColor::black;
                z = grandpa;
            }
            else {
                if (RBTree::isLeftDesc(z)) {
                    z = parent;
                    tree.RightRotate(z);
                    parent = z->parent.lock();
                    grandpa = parent->parent.lock();
                }
                parent->color = NodeColor::black;
                grandpa->color = NodeColor::red;
            }
        }
    }
    tree.root->color = NodeColor::black;
}
