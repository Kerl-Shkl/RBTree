#ifndef INCLUDE_DELETEFIXUPER_H
#define INCLUDE_DELETEFIXUPER_H

#include "Node.h"

class IRBTree;

class DeleteFixuper
{
public:
    DeleteFixuper(IRBTree& tree);

    void Delete(std::shared_ptr<Node> z);

private:
    void MyFixUp(std::shared_ptr<Node> x);

    void tryPaint(const std::shared_ptr<Node>& node, NodeColor color) const;
    bool isTrivial(const std::shared_ptr<const Node>& z) const;
    std::shared_ptr<Node> solveTrivial(const std::shared_ptr<Node>& z);
    std::shared_ptr<Node> solveNoneTrivial(const std::shared_ptr<Node>& z);
    void clearProxy();

    void addProxyNils(const std::shared_ptr<Node>& node);
    std::shared_ptr<Node> getProxy();
    void setParentAndSibling(const std::shared_ptr<Node>& x);
    bool isFirstCase() const;
    bool isSecondCase() const;
    bool isThirdCase() const;
    void solveFirstCase(std::shared_ptr<Node>& x);
    void solveSecondCase(std::shared_ptr<Node>& x);
    void solveThirdCase(std::shared_ptr<Node>& x);
    void solveFourthCase(std::shared_ptr<Node>& x);

    std::shared_ptr<Node> proxy_nil;
    bool need_fixup;

    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> sibling;
    IRBTree& tree;

    friend class DeleteFixuper_fixture;
};

#endif  // end of include guard: INCLUDE_DELETEFIXUPER_H
