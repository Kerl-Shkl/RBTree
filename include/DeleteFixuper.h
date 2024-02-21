#ifndef INCLUDE_DELETEFIXUPER_H
#define INCLUDE_DELETEFIXUPER_H

#include "Node.h"

class IRBTree;

class DeleteFixuper
{
public:
    DeleteFixuper(IRBTree& tree);
    void FixUp(std::shared_ptr<Node> x);
    void MyFixUp(std::shared_ptr<Node> x);

private:
    void setParentAndSibling(const std::shared_ptr<Node>& x);
    bool isFirstCase() const;
    bool isSecondCase() const;
    bool isThirdCase() const;
    void solveFirstCase(std::shared_ptr<Node>& x);
    void solveSecondCase(std::shared_ptr<Node>& x);
    void solveThirdCase(std::shared_ptr<Node>& x);
    void solveFourthCase(std::shared_ptr<Node>& x);

    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> sibling;
    IRBTree& tree;

    friend class DeleteFixuper_fixture;
};

#endif  // end of include guard: INCLUDE_DELETEFIXUPER_H
