#ifndef INCLUDE_RBTREEREFACTOR_H
#define INCLUDE_RBTREEREFACTOR_H

#include "IRBTree.h"

class RBTreeRefactor : public IRBTree
{
public:
    virtual RBIterator Insert(int value) override;
    virtual RBIterator Delete(RBIterator it) override;
    virtual RBIterator Find(int value) const override;
    virtual size_t Size() const override;
    virtual RBIterator begin() const override;
    virtual RBIterator end() const override;
    virtual bool Empty() const override;

protected:
    virtual std::shared_ptr<Node>& getRoot() override;
    virtual const std::shared_ptr<Node>& getRoot() const override;

    virtual void
    Rotate(std::shared_ptr<Node>& x, std::shared_ptr<Node> Node::*first_desc,
           std::shared_ptr<Node> Node::*second_desc);
    virtual void Transplant(std::shared_ptr<Node> u, std::shared_ptr<Node> v);
    virtual void InsertNode(std::shared_ptr<Node> x);
    virtual void DeleteNode(std::shared_ptr<Node> x);

private:
    virtual void LeftRotate(std::shared_ptr<Node> x) override;
    virtual void RightRotate(std::shared_ptr<Node> x) override;
    void doInsertFixUp(std::shared_ptr<Node> x);
    void doDeleteFixUp(std::shared_ptr<Node> x);
    std::shared_ptr<Node> findFutureParent(int value) const;
    virtual std::shared_ptr<Node> minimumDesc(std::shared_ptr<Node> x) override;
    int getSize(const std::shared_ptr<Node>& x) const;
    std::shared_ptr<Node> findNodeWithValue(int value) const;
    bool hasValue(const std::shared_ptr<Node>& node, int value) const;

    // static std::shared_ptr<Node> minimumDesc(std::shared_ptr<Node> x);
    // static bool isLeftDesc(const std::shared_ptr<Node>& x);
    // static bool isRightDesc(const std::shared_ptr<Node>& x);
    // static bool isRed(const std::shared_ptr<Node>& x);
    // static bool isBlack(const std::shared_ptr<Node>& x);

    std::shared_ptr<Node> root;

    friend class InsertFixuper;
};

#endif  // end of include guard: INCLUDE_RBTREEREFACTOR_H
