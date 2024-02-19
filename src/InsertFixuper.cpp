#include "InsertFixuper.h"
#include "RBTree.h"

InsertFixuper::InsertFixuper(RBTree& rbtree)
: tree(rbtree)
{}

void InsertFixuper::FixUp(std::shared_ptr<Node> z)
{
    while (RBTree::isRed(z->parent.lock())) {
        FixUpNode(z);
    }
    tree.root->color = NodeColor::black;
}

void InsertFixuper::FixUpNode(std::shared_ptr<Node>& z)
{
    updateAncestors(z);
    auto uncle = getUncle();
    if (RBTree::isRed(uncle)) {
        parent->color = NodeColor::black;
        uncle->color = NodeColor::black;
        grandpa->color = NodeColor::red;
        z = grandpa;
    }
    else {
        SolveRotation(z);
    }
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

void InsertFixuper::SolveRotation(std::shared_ptr<Node>& z)
{
    if (RBTree::isLeftDesc(parent)) {
        doSolveRotation(z, &RBTree::isRightDesc, &RBTree::LeftRotate,
                        &RBTree::RightRotate);
    }
    else {
        doSolveRotation(z, &RBTree::isLeftDesc, &RBTree::RightRotate,
                        &RBTree::LeftRotate);
    }
}

void InsertFixuper::doSolveRotation(
    std::shared_ptr<Node>& z, bool (*isSideDesc)(const std::shared_ptr<Node>&),
    void (RBTree::*firstRotate)(std::shared_ptr<Node>),
    void (RBTree::*secondRotate)(std::shared_ptr<Node>))
{
    if (isSideDesc(z)) {
        z = parent;
        (tree.*firstRotate)(z);
        updateAncestors(z);
    }
    parent->color = NodeColor::black;
    grandpa->color = NodeColor::red;
    (tree.*secondRotate)(grandpa);
}
