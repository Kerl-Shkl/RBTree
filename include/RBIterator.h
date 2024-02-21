#ifndef INCLUDE_RBITERATOR_H
#define INCLUDE_RBITERATOR_H

#include "Node.h"
#include <iterator>

class RBTree;

class RBIterator : std::iterator<std::bidirectional_iterator_tag, int>
{
public:
    explicit RBIterator(const RBTree& tree);
    const int& operator*();
    RBIterator& operator++();
    RBIterator operator++(int);
    RBIterator& operator--();
    RBIterator operator--(int);

private:
    std::shared_ptr<Node> getNode();
    std::shared_ptr<Node> node;
};

#endif  // end of include guard: INCLUDE_RBITERATOR_H
