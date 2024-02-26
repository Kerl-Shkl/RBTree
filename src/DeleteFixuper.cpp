#include "DeleteFixuper.h"
#include "IRBTree.h"

DeleteFixuper::DeleteFixuper(IRBTree& tree)
: need_fixup(false)
, tree(tree)
{}

std::shared_ptr<Node> DeleteFixuper::getProxy()
{
    if (proxy_nil == nullptr) {
        proxy_nil = std::make_shared<Node>(Node{.color = NodeColor::black});
    }
    return proxy_nil;
}

void DeleteFixuper::addProxyNils(const std::shared_ptr<Node>& node)
{
    if (node->left == nullptr) {
        node->left = getProxy();
        proxy_nil->parent = node;
    }
    if (node->right == nullptr) {
        node->right = getProxy();
        proxy_nil->parent = node;
    }
}

void DeleteFixuper::Delete(std::shared_ptr<Node> z)
{
    std::shared_ptr<Node> x{nullptr};
    if (isTrivial(z)) {
        x = solveTrivial(z);
    }
    else {
        x = solveNoneTrivial(z);
    }
    if (need_fixup) {
        MyFixUp(x);
    }
    clearProxy();
}

void DeleteFixuper::tryPaint(const std::shared_ptr<Node>& node,
                             NodeColor color) const
{
    if (node != nullptr) {
        node->color = color;
    }
}

bool DeleteFixuper::isTrivial(const std::shared_ptr<const Node>& z) const
{
    return z->left == nullptr || z->right == nullptr;
}

std::shared_ptr<Node>
DeleteFixuper::solveTrivial(const std::shared_ptr<Node>& z)
{
    addProxyNils(z);
    std::shared_ptr<Node> x{nullptr};
    need_fixup = z->color == NodeColor::black;
    if (z->left == proxy_nil) {
        x = z->right;
        tree.Transplant(z, z->right);
    }
    else if (z->right == proxy_nil) {
        x = z->left;
        tree.Transplant(z, z->left);
    }
    return x;
}

std::shared_ptr<Node>
DeleteFixuper::solveNoneTrivial(const std::shared_ptr<Node>& z)
{
    auto y = IRBTree::minimumDesc(z->right);
    need_fixup = y->color == NodeColor::black;
    addProxyNils(y);
    auto x = y->right;
    if (y->parent.lock() == z) {
        x->parent = y;
    }
    else {
        tree.Transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
    }
    tree.Transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
    return x;
}

void DeleteFixuper::clearProxy()
{
    if (proxy_nil == nullptr) {
        return;
    }
    auto prox_parent = proxy_nil->parent.lock();
    if (prox_parent->left == proxy_nil) {
        prox_parent->left.reset();
    }
    if (prox_parent->right == proxy_nil) {
        prox_parent->right.reset();
    }
    proxy_nil.reset();
}

void DeleteFixuper::MyFixUp(std::shared_ptr<Node> x)
{
    while (x != tree.getRoot() && tree.isBlack(x)) {
        setParentAndSibling(x);
        if (isFirstCase()) {
            solveFirstCase(x);
        }
        if (isSecondCase()) {
            solveSecondCase(x);
        }
        else {
            if (isThirdCase()) {
                solveThirdCase(x);
            }
            solveFourthCase(x);
        }
    }
    x->color = NodeColor::black;
}

void DeleteFixuper::setParentAndSibling(const std::shared_ptr<Node>& x)
{
    parent = x->parent.lock();
    sibling = tree.isLeftDesc(x) ? parent->right : parent->left;
}

bool DeleteFixuper::isFirstCase() const
{
    return tree.isRed(sibling);
}

bool DeleteFixuper::isSecondCase() const
{
    return tree.isBlack(sibling->left) && tree.isBlack(sibling->right);
}

bool DeleteFixuper::isThirdCase() const
{
    auto sibling_desc =
        tree.isLeftDesc(sibling) ? sibling->left : sibling->right;
    return tree.isBlack(sibling_desc);
}

void DeleteFixuper::solveFirstCase(std::shared_ptr<Node>& x)
{
    sibling->color = NodeColor::black;
    parent->color = NodeColor::red;
    if (tree.isLeftDesc(x)) {
        tree.LeftRotate(parent);
    }
    else {
        tree.RightRotate(parent);
    }
    setParentAndSibling(x);
}

void DeleteFixuper::solveSecondCase(std::shared_ptr<Node>& x)
{
    sibling->color = NodeColor::red;
    x = parent;
}

void DeleteFixuper::solveThirdCase(std::shared_ptr<Node>& x)
{
    sibling->color = NodeColor::red;
    if (tree.isLeftDesc(x)) {
        tryPaint(sibling->left, NodeColor::black);
        tree.RightRotate(sibling);
    }
    else {
        tryPaint(sibling->right, NodeColor::black);
        tree.LeftRotate(sibling);
    }
    setParentAndSibling(x);
}

void DeleteFixuper::solveFourthCase(std::shared_ptr<Node>& x)
{
    sibling->color = parent->color;
    parent->color = NodeColor::black;
    if (tree.isLeftDesc(x)) {
        tryPaint(sibling->right, NodeColor::black);
        tree.LeftRotate(parent);
    }
    else {
        tryPaint(sibling->left, NodeColor::black);
        tree.RightRotate(parent);
    }
    x = tree.getRoot();
}
