#include "DeleteFixuper.h"
#include "Node.h"
#include "RBTree.h"
#include <gtest/gtest.h>

class RBTree_fixture : public testing::Test
{
protected:
    void SetUp() override
    {}

    std::shared_ptr<Node>& getRoot()
    {
        return tree.root;
    }

    RBTree tree;
};

class DeleteFixuper_fixture : public RBTree_fixture
{
protected:
    DeleteFixuper_fixture()
    : fixuper(tree)
    {}

    void SetUp() override
    {}

    void startSolveFirstCase(std::shared_ptr<Node> x)
    {
        fixuper.setParentAndSibling(x);
        fixuper.solveFirstCase(x);
    }

    DeleteFixuper fixuper;
};

TEST_F(DeleteFixuper_fixture, FirstCaseLeft)
{
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Insert(12);
    tree.Insert(20);
    auto& root = tree.root;
    root->color = NodeColor::black;
    root->right->color = NodeColor::red;
    root->right->left->color = NodeColor::black;
    root->right->right->color = NodeColor::black;
    root->left->color = NodeColor::black;

    startSolveFirstCase(root->left);

    EXPECT_EQ(root->value, 15);
    EXPECT_EQ(root->color, NodeColor::black);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->left->color, NodeColor::red);
    EXPECT_EQ(root->left->left->value, 5);
    EXPECT_EQ(root->left->left->color, NodeColor::black);
    EXPECT_EQ(root->left->right->value, 12);
    EXPECT_EQ(root->left->right->color, NodeColor::black);
    EXPECT_EQ(root->right->value, 20);
    EXPECT_EQ(root->right->color, NodeColor::black);
}

TEST_F(DeleteFixuper_fixture, FirstCaseRight)
{
    tree.Insert(10);
    tree.Insert(15);
    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(2);
    auto& root = tree.root;
    root->color = NodeColor::black;
    root->left->color = NodeColor::red;
    root->left->left->color = NodeColor::black;
    root->left->right->color = NodeColor::black;
    root->right->color = NodeColor::black;

    startSolveFirstCase(root->right);

    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->color, NodeColor::black);
    EXPECT_EQ(root->right->value, 10);
    EXPECT_EQ(root->right->color, NodeColor::red);
    EXPECT_EQ(root->right->left->value, 7);
    EXPECT_EQ(root->right->left->color, NodeColor::black);
    EXPECT_EQ(root->right->right->value, 15);
    EXPECT_EQ(root->right->right->color, NodeColor::black);
    EXPECT_EQ(root->left->value, 2);
    EXPECT_EQ(root->left->color, NodeColor::black);
}
