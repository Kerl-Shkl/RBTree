#ifndef INCLUDE_NODE_H
#define INCLUDE_NODE_H

#include <memory>

enum class NodeColor
{
    red,
    black
};

struct Node
{
    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::weak_ptr<Node> parent;
    NodeColor color;
};

#endif  // end of include guard: INCLUDE_NODE_H
