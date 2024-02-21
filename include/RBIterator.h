#ifndef INCLUDE_RBITERATOR_H
#define INCLUDE_RBITERATOR_H

#include "Node.h"
// #include <iterator>

class IRBTree;

class RBIterator  
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = int;
    using difference_type = int;
    using pointer = int *;
    using reference = int&;

    explicit RBIterator(const IRBTree& tree);
    const int& operator*();
    RBIterator& operator++();
    RBIterator operator++(int);
    RBIterator& operator--();
    RBIterator operator--(int);

private:
    explicit RBIterator(std::shared_ptr<Node> node);
    std::shared_ptr<Node> getNode();

    std::shared_ptr<Node> node;

    friend class RBTreeRefactor;
    friend bool operator==(const RBIterator&, const RBIterator&);
};

bool operator==(const RBIterator& a, const RBIterator& b);

#endif  // end of include guard: INCLUDE_RBITERATOR_H
