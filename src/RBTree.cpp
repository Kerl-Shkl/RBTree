#include "RBTree.h"
#include "InsertFixuper.h"

void RBTree::Insert(int value)
{
    auto new_node = std::make_shared<Node>();
    new_node->value = value;
    InsertNode(std::move(new_node));
}

void RBTree::InsertNode(std::shared_ptr<Node> z)
{
    std::shared_ptr<Node> parent = findParent(z->value);
    z->parent = parent;
    if (parent == nullptr) {
        root = z;
    }
    else if (z->value < parent->value) {
        parent->left = z;
    }
    else {
        parent->right = z;
    }
    z->color = NodeColor::red;
    doInsertFixUp(std::move(z));
}

std::shared_ptr<Node> RBTree::findParent(int value)
{
    std::shared_ptr<Node> parent{nullptr};
    auto x = root;
    while (x != nullptr) {
        parent = x;
        if (value < x->value) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    return parent;
}

void RBTree::doInsertFixUp(std::shared_ptr<Node> x)
{
    InsertFixuper fixuper(*this);
    fixuper.FixUp(std::move(x));
}

void RBTree::Delete(std::shared_ptr<Node>& z)
{
    auto y = z;
    NodeColor y_original_color = y->color;
    std::shared_ptr<Node> x{nullptr};
    if (z->left == nullptr) {
        x = z->right;
        Transplant(z, z->right);
    }
    else if (z->right == nullptr) {
        x = z->left;
        Transplant(z, z->left);
    }
    else {
        y = minimumDesc(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent.lock() == z) {
            x->parent = y;
        }
        else {
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == NodeColor::black) {
        // FixUp
    }
}

void RBTree::Transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v)
{
    if (u->parent.expired()) {
        root = v;
    }
    else if (isLeftDesc(u)) {
        auto parent = u->parent.lock();
        parent->left = v;
    }
    else {
        auto parent = u->parent.lock();
        parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

void RBTree::LeftRotate(std::shared_ptr<Node> x)
{
    Rotate(x, &Node::left, &Node::right);
}

void RBTree::RightRotate(std::shared_ptr<Node> x)
{
    Rotate(x, &Node::right, &Node::left);
}

void RBTree::Rotate(std::shared_ptr<Node>& x,
                    std::shared_ptr<Node> Node::*first_desc,
                    std::shared_ptr<Node> Node::*second_desc)
{
    auto second = (*x).*second_desc;
    (*x).*second_desc = (*second).*first_desc;

    if ((*second).*first_desc != nullptr) {
        ((*second).*first_desc)->parent = x;
    }
    second->parent = x->parent;
    if (x->parent.expired()) {
        root = second;
    }
    else if (isLeftDesc(x)) {
        auto parent = x->parent.lock();
        parent->left = second;
    }
    else {
        auto parent = x->parent.lock();
        parent->right = second;
    }
    (*second).*first_desc = x;
    x->parent = second;
}

bool RBTree::isLeftDesc(const std::shared_ptr<Node>& x)
{
    auto parent = x->parent.lock();
    return parent->left == x;
}

bool RBTree::isRightDesc(const std::shared_ptr<Node>& x)
{
    return !isLeftDesc(x);
}

bool RBTree::isRed(const std::shared_ptr<Node>& x)
{
    return x ? x->color == NodeColor::red : false;
}

std::shared_ptr<Node> minimumDesc(std::shared_ptr<Node> x)
{
    while (x->left != nullptr) {
        x = x->left;
    }
    return x;
}
