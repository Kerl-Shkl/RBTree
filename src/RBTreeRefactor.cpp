#include "DeleteFixuper.h"
#include "InsertFixuper.h"
#include <RBTreeRefactor.h>
#include <exception>

RBIterator RBTreeRefactor::Insert(int value)
{
    auto new_node = std::make_shared<Node>();
    new_node->value = value;
    InsertNode(std::move(new_node));
    return RBIterator{new_node};
}

RBIterator RBTreeRefactor::Delete(RBIterator it)
{
    RBIterator next_it = it;
    ++next_it;
    DeleteNode(it.getNode());
    return next_it;
}

RBIterator RBTreeRefactor::Find(int value) const
{
    throw std::runtime_error{"Not implemented yet"};
}

size_t RBTreeRefactor::Size() const
{
    throw std::runtime_error{"Not implemented yet"};
}

RBIterator RBTreeRefactor::begin() const
{
    return RBIterator{root};
}

RBIterator RBTreeRefactor::end() const
{
    return RBIterator{nullptr};
}

bool RBTreeRefactor::Empty() const
{
    return root == nullptr;
}

std::shared_ptr<Node>& RBTreeRefactor::getRoot()
{
    return root;
}

const std::shared_ptr<Node>& RBTreeRefactor::getRoot() const
{
    return root;
}

void RBTreeRefactor::LeftRotate(std::shared_ptr<Node> x)
{
    Rotate(x, &Node::left, &Node::right);
}

void RBTreeRefactor::RightRotate(std::shared_ptr<Node> x)
{
    Rotate(x, &Node::right, &Node::left);
}

void RBTreeRefactor::Transplant(std::shared_ptr<Node> u,
                                std::shared_ptr<Node> v)
{
    if (u->parent.expired()) {
        root = v;
    }
    else {
        auto parent = u->parent.lock();
        if (isLeftDesc(u)) {
            parent->left = v;
        }
        else {
            parent->right = v;
        }
    }

    if (v != nullptr) {
        v->parent = u->parent;
    }
}

void RBTreeRefactor::InsertNode(std::shared_ptr<Node> z)
{
    std::shared_ptr<Node> parent = findFutureParent(z->value);
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

void RBTreeRefactor::DeleteNode(std::shared_ptr<Node> z)
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
            if (x != nullptr) {
                x->parent = y;
            }
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
        doDeleteFixUp(x);
    }
}

void RBTreeRefactor::doInsertFixUp(std::shared_ptr<Node> x)
{
    InsertFixuper fixuper(*this);
    fixuper.FixUp(std::move(x));
}

void RBTreeRefactor::doDeleteFixUp(std::shared_ptr<Node> x)
{
    DeleteFixuper fixuper(*this);
    fixuper.MyFixUp(std::move(x));
}

void RBTreeRefactor::Rotate(std::shared_ptr<Node>& x,
                            std::shared_ptr<Node> Node::*first_desc,
                            std::shared_ptr<Node> Node::*second_desc)
{
    auto second = (*x).*second_desc;
    (*x).*second_desc = (*second).*first_desc;

    if ((*second).*first_desc != nullptr) {
        ((*second).*first_desc)->parent = x;
    }
    Transplant(x, second);
    (*second).*first_desc = x;
    x->parent = second;
}

std::shared_ptr<Node> RBTreeRefactor::findFutureParent(int value)
{
    std::shared_ptr<Node> parent{nullptr};
    auto x = root;
    while (x != nullptr) {
        parent = x;
        x = value < x->value ? x->left : x->right;
    }
    return parent;
}

std::shared_ptr<Node> RBTreeRefactor::minimumDesc(std::shared_ptr<Node> x)
{
    while (x->left != nullptr) {
        x = x->left;
    }
    return x;
}

bool RBTreeRefactor::isLeftDesc(const std::shared_ptr<Node>& x)
{
    auto parent = x->parent.lock();
    return parent->left == x;
}

bool RBTreeRefactor::isRightDesc(const std::shared_ptr<Node>& x)
{
    return !isLeftDesc(x);
}

bool RBTreeRefactor::isRed(const std::shared_ptr<Node>& x)
{
    return x ? x->color == NodeColor::red : false;
}

bool RBTreeRefactor::isBlack(const std::shared_ptr<Node>& x)
{
    return !isRed(x);
}