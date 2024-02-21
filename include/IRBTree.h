#ifndef INCLUDE_IRBTREE_H
#define INCLUDE_IRBTREE_H

#include "Node.h"
#include "RBIterator.h"
#include <memory>

class IRBTree
{
public:
    virtual RBIterator Insert(int value) = 0;
    virtual RBIterator Delete(RBIterator it) = 0;
    virtual RBIterator Find(int value) const = 0;
    virtual RBIterator begin() const = 0;
    virtual RBIterator end() const = 0;
    virtual size_t Size() const = 0;
    virtual bool Empty() const = 0;

protected:
    virtual std::shared_ptr<Node>& getRoot() = 0;
    virtual const std::shared_ptr<Node>& getRoot() const = 0;

    friend class RBIterator;
};

#endif  // end of include guard: INCLUDE_IRBTREE_H
