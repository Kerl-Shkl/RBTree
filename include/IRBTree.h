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
    // virtual std::shared_ptr<Node>
    // minimumDesc(std::shared_ptr<Node> x) const = 0;
    static std::shared_ptr<Node> minimumDesc(std::shared_ptr<Node> x);
    static std::shared_ptr<Node> maximumDesc(std::shared_ptr<Node> x);

    virtual void LeftRotate(std::shared_ptr<Node> x) = 0;
    virtual void RightRotate(std::shared_ptr<Node> x) = 0;

    virtual bool isLeftDesc(const std::shared_ptr<Node>& x);
    virtual bool isRightDesc(const std::shared_ptr<Node>& x);
    virtual bool isRed(const std::shared_ptr<Node>& x);
    virtual bool isBlack(const std::shared_ptr<Node>& x);

    friend class RBIterator;
    friend class InsertFixuper;
    friend class DeleteFixuper;
};

#endif  // end of include guard: INCLUDE_IRBTREE_H
