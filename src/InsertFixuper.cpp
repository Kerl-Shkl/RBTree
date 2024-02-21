#include "InsertFixuper.h"
#include "IRBTree.h"

InsertFixuper::InsertFixuper(IRBTree& rbtree)
: tree(rbtree)
{}

void InsertFixuper::FixUp(std::shared_ptr<Node> z)
{
    while (tree.isRed(z->parent.lock())) {
        FixUpNode(z);
    }
    tree.getRoot()->color = NodeColor::black;
}

void InsertFixuper::FixUpNode(std::shared_ptr<Node>& z)
{
    updateAncestors(z);
    auto uncle = getUncle();
    if (tree.isRed(uncle)) {
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

    return tree.isLeftDesc(parent) ? grandpa->right : grandpa->left;
}

void InsertFixuper::SolveRotation(std::shared_ptr<Node>& z)
{
    if (tree.isLeftDesc(parent)) {
        doSolveRotation(z, &IRBTree::isRightDesc, &IRBTree::LeftRotate,
                        &IRBTree::RightRotate);
    }
    else {
        doSolveRotation(z, &IRBTree::isLeftDesc, &IRBTree::RightRotate,
                        &IRBTree::LeftRotate);
    }
}

void InsertFixuper::doSolveRotation(
    std::shared_ptr<Node>& z,
    bool (IRBTree::*isSideDesc)(const std::shared_ptr<Node>&) const,
    void (IRBTree::*firstRotate)(std::shared_ptr<Node>),
    void (IRBTree::*secondRotate)(std::shared_ptr<Node>))
{
    if ((tree.*isSideDesc)(z)) {
        z = parent;
        (tree.*firstRotate)(z);
        updateAncestors(z);
    }
    parent->color = NodeColor::black;
    grandpa->color = NodeColor::red;
    (tree.*secondRotate)(grandpa);
}
