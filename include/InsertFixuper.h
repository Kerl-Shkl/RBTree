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
    RBTree& tree;
};

#endif  // end of include guard: INCLUDE_INSERTFIXUPER_H
