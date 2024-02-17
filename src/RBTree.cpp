#include "RBTree.h"

void RBTree::Insert(int value)
{
    auto new_node = std::make_shared<Node>();
    new_node->value = value;
    InsertNode(std::move(new_node));
}

void RBTree::InsertNode(std::shared_ptr<Node> z)
{
    std::shared_ptr<Node> parent{nullptr};
    auto x = root;
    while (x != nullptr) {
        parent = x;
        if (z->value < x->value) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
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
    // InsertFixup
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
