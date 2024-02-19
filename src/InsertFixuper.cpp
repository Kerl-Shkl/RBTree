#include "InsertFixuper.h"
#include "RBTree.h"

InsertFixuper::InsertFixuper(RBTree& rbtree)
: tree(rbtree)
{}

void InsertFixuper::FixUp(std::shared_ptr<Node> z)
{
    while (RBTree::isRed(z->parent.lock())) {
        updateAncestors(z);
        if (RBTree::isLeftDesc(parent)) {
            auto uncle = getUncle();
            if (RBTree::isRed(uncle)) {
                parent->color = NodeColor::black;
                uncle->color = NodeColor::black;
                grandpa->color = NodeColor::red;
                z = grandpa;
            }
            else {
                if (RBTree::isRightDesc(z)) {
                    z = parent;
                    tree.LeftRotate(z);
                    updateAncestors(z);
                }
                parent->color = NodeColor::black;
                grandpa->color = NodeColor::red;
                tree.RightRotate(grandpa);
            }
        }
        else {
            auto uncle = getUncle();
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
                    updateAncestors(z);
                }
                parent->color = NodeColor::black;
                grandpa->color = NodeColor::red;
                tree.LeftRotate(grandpa);
            }
        }
    }
    tree.root->color = NodeColor::black;
}

void InsertFixuper::updateAncestors(const std::shared_ptr<Node>& child)
{
    parent = child->parent.lock();
    grandpa = parent->parent.lock();
}

std::shared_ptr<Node> InsertFixuper::getUncle() const
{

    return RBTree::isLeftDesc(parent) ? grandpa->right : grandpa->left;
}
