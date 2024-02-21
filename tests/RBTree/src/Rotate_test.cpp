#include "RBTreeRefactor.h"
#include <gtest/gtest.h>

class OpenRBTree : public RBTreeRefactor
{
public:
    using RBTreeRefactor::getRoot;
    using RBTreeRefactor::LeftRotate;
    using RBTreeRefactor::RightRotate;
};

class RBTree_fixture : public testing::Test
{
protected:
    void SetUp() override
    {
        auto root = std::make_shared<Node>();
        root->value = 10;
        auto ld = std::make_shared<Node>();
        ld->value = 5;
        auto rd = std::make_shared<Node>();
        rd->value = 15;
        auto lld = std::make_shared<Node>();
        lld->value = 3;
        auto lrd = std::make_shared<Node>();
        lrd->value = 7;
        auto rld = std::make_shared<Node>();
        rld->value = 13;
        auto rrd = std::make_shared<Node>();
        rrd->value = 17;

        root->left = ld;
        root->right = rd;
        ld->parent = root;
        rd->parent = root;
        ld->left = lld;
        ld->right = lrd;
        lld->parent = ld;
        lrd->parent = ld;
        rd->left = rld;
        rd->right = rrd;
        rld->parent = rd;
        rrd->parent = rd;

        tree.getRoot() = root;
    }

    OpenRBTree tree;
};

TEST_F(RBTree_fixture, LeftRootRotate)
{
    auto& root = tree.getRoot();
    tree.LeftRotate(root);
    EXPECT_EQ(root->value, 15);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 17);
    EXPECT_EQ(root->left->left->value, 5);
    EXPECT_EQ(root->left->right->value, 13);
}

TEST_F(RBTree_fixture, RightRootRotate)
{
    auto& root = tree.getRoot();
    tree.RightRotate(root);
    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->left->value, 3);
    EXPECT_EQ(root->right->value, 10);
    EXPECT_EQ(root->right->left->value, 7);
    EXPECT_EQ(root->right->right->value, 15);
}

TEST_F(RBTree_fixture, LeftRotate)
{
    auto& root = tree.getRoot();
    tree.LeftRotate(root->left);
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left->value, 7);
    EXPECT_EQ(root->right->value, 15);
    EXPECT_EQ(root->left->left->value, 5);
    EXPECT_EQ(root->left->left->left->value, 3);

    EXPECT_EQ(root->left->parent.lock(), root);
    EXPECT_EQ(root->left->left->parent.lock(), root->left);
    EXPECT_EQ(root->left->left->left->parent.lock(), root->left->left);
}

TEST_F(RBTree_fixture, RightRotate)
{
    auto& root = tree.getRoot();
    tree.RightRotate(root->left);
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left->value, 3);
    EXPECT_EQ(root->right->value, 15);
    EXPECT_EQ(root->left->right->value, 5);
    EXPECT_EQ(root->left->right->right->value, 7);

    EXPECT_EQ(root->left->parent.lock(), root);
    EXPECT_EQ(root->left->right->parent.lock(), root->left);
    EXPECT_EQ(root->left->right->right->parent.lock(), root->left->right);
}
