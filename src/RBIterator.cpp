#include "RBIterator.h"
#include "IRBTree.h"

RBIterator::RBIterator(const IRBTree& tree)
{
    node = tree.begin().node;
}

const int& RBIterator::operator*()
{
    return node->value;
}

RBIterator& RBIterator::operator++()
{
    if (node->right != nullptr) {
        node = node->right;
    }
    else {
        auto temp = node->parent.lock();
        while (temp != nullptr && temp->value < node->value) {
            temp = temp->parent.lock();
        }
        node = temp;
    }
    return *this;
}

RBIterator RBIterator::operator++(int)
{
    RBIterator temp = *this;
    operator++();
    return temp;
}

RBIterator& RBIterator::operator--()
{
    if (node->left != nullptr) {
        node = node->left;
    }
    else {
        auto temp = node->parent.lock();
        while (temp != nullptr && temp->value > node->value) {
            temp = temp->parent.lock();
        }
        node = temp;
    }
    return *this;
}

RBIterator RBIterator::operator--(int)
{
    RBIterator temp = *this;
    operator--();
    return *this;
}

std::shared_ptr<Node> RBIterator::getNode()
{
    return node;
}

RBIterator::RBIterator(std::shared_ptr<Node> node)
: node(std::move(node))
{}
