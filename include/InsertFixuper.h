#ifndef INCLUDE_INSERTFIXUPER_H
#define INCLUDE_INSERTFIXUPER_H

#include "Node.h"

class RBTree;

class InsertFixuper
{
public:
    InsertFixuper(RBTree& rbtree);
    void FixUp(std::shared_ptr<Node> z);

private:
    // static std::shared_ptr<Node> getUncle(const std::shared_ptr<Node>& x);
    void updateAncestors(const std::shared_ptr<Node>& child);
    std::shared_ptr<Node> getUncle() const;

    RBTree& tree;
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> grandpa;
};

#endif  // end of include guard: INCLUDE_INSERTFIXUPER_H
