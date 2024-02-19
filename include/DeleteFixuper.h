#ifndef INCLUDE_DELETEFIXUPER_H
#define INCLUDE_DELETEFIXUPER_H

#include "Node.h"

class RBTree;

class DeleteFixuper
{
public:
    DeleteFixuper(RBTree& tree);
    void FixUp(std::shared_ptr<Node> x);

private:
    RBTree& tree;
};

#endif  // end of include guard: INCLUDE_DELETEFIXUPER_H
