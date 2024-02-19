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
    void FixUpNode(std::shared_ptr<Node>& z);
    void updateAncestors(const std::shared_ptr<Node>& child);
    std::shared_ptr<Node> getUncle() const;
    void SolveRotation(std::shared_ptr<Node>& z);
    void doSolveRotation(std::shared_ptr<Node>& z,
                         bool (*isSideDesc)(const std::shared_ptr<Node>&),
                         void (RBTree::*firstRotate)(std::shared_ptr<Node>),
                         void (RBTree::*secondRotate)(std::shared_ptr<Node>));

    RBTree& tree;
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> grandpa;
};

#endif  // end of include guard: INCLUDE_INSERTFIXUPER_H
