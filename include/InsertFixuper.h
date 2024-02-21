#ifndef INCLUDE_INSERTFIXUPER_H
#define INCLUDE_INSERTFIXUPER_H

#include "Node.h"

class IRBTree;

class InsertFixuper
{
public:
    InsertFixuper(IRBTree& rbtree);
    void FixUp(std::shared_ptr<Node> z);

private:
    void FixUpNode(std::shared_ptr<Node>& z);
    void updateAncestors(const std::shared_ptr<Node>& child);
    std::shared_ptr<Node> getUncle() const;
    void SolveRotation(std::shared_ptr<Node>& z);
    void doSolveRotation(
        std::shared_ptr<Node>& z,
        bool (IRBTree::*isSideDesc)(const std::shared_ptr<Node>&) const,
        void (IRBTree::*firstRotate)(std::shared_ptr<Node>),
        void (IRBTree::*secondRotate)(std::shared_ptr<Node>));

    IRBTree& tree;
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> grandpa;
};

#endif  // end of include guard: INCLUDE_INSERTFIXUPER_H
