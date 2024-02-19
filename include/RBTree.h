#ifndef INCLUDE_RBTREE_H
#define INCLUDE_RBTREE_H

#include "Node.h"

class RBTree
{
public:
    void Insert(int value);
    void Delete(std::shared_ptr<Node>& x);

    // protected:
    virtual void
    Rotate(std::shared_ptr<Node>& x, std::shared_ptr<Node> Node::*first_desc,
           std::shared_ptr<Node> Node::*second_desc);
    virtual void InsertNode(std::shared_ptr<Node> x);
    void Transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v);

    // private:

    static std::shared_ptr<Node> minimumDesc(std::shared_ptr<Node> x);
    static bool isLeftDesc(const std::shared_ptr<Node>& x);
    static bool isRightDesc(const std::shared_ptr<Node>& x);
    static bool isRed(const std::shared_ptr<Node>& x);
    std::shared_ptr<Node> findParent(int value);
    void LeftRotate(std::shared_ptr<Node> x);
    void RightRotate(std::shared_ptr<Node> x);
    void doInsertFixUp(std::shared_ptr<Node> x);

protected:
    std::shared_ptr<Node> root;

    friend class RBTree_fixture;
};

#endif  // end of include guard: INCLUDE_RBTREE_H
