#include "RBTree.h"
#include <gtest/gtest.h>

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

        tree.root = root;
    }

    RBTree tree;
};

TEST_F(RBTree_fixture, LeftRootRotate)
{
    tree.LeftRotate(tree.root);
    EXPECT_EQ(tree.root->value, 15);
    EXPECT_EQ(tree.root->left->value, 10);
    EXPECT_EQ(tree.root->right->value, 17);
    EXPECT_EQ(tree.root->left->left->value, 5);
    EXPECT_EQ(tree.root->left->right->value, 13);
}

TEST_F(RBTree_fixture, RightRootRotate)
{
    tree.RightRotate(tree.root);
    EXPECT_EQ(tree.root->value, 5);
    EXPECT_EQ(tree.root->left->value, 3);
    EXPECT_EQ(tree.root->right->value, 10);
    EXPECT_EQ(tree.root->right->left->value, 7);
    EXPECT_EQ(tree.root->right->right->value, 15);
}

TEST_F(RBTree_fixture, LeftRotate)
{
    tree.LeftRotate(tree.root->left);
    EXPECT_EQ(tree.root->value, 10);
    EXPECT_EQ(tree.root->left->value, 7);
    EXPECT_EQ(tree.root->right->value, 15);
    EXPECT_EQ(tree.root->left->left->value, 5);
    EXPECT_EQ(tree.root->left->left->left->value, 3);

    EXPECT_EQ(tree.root->left->parent.lock(), tree.root);
    EXPECT_EQ(tree.root->left->left->parent.lock(), tree.root->left);
    EXPECT_EQ(tree.root->left->left->left->parent.lock(),
              tree.root->left->left);
}

TEST_F(RBTree_fixture, RightRotate)
{
    tree.RightRotate(tree.root->left);
    EXPECT_EQ(tree.root->value, 10);
    EXPECT_EQ(tree.root->left->value, 3);
    EXPECT_EQ(tree.root->right->value, 15);
    EXPECT_EQ(tree.root->left->right->value, 5);
    EXPECT_EQ(tree.root->left->right->right->value, 7);

    EXPECT_EQ(tree.root->left->parent.lock(), tree.root);
    EXPECT_EQ(tree.root->left->right->parent.lock(), tree.root->left);
    EXPECT_EQ(tree.root->left->right->right->parent.lock(),
              tree.root->left->right);
}
