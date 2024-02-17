#include "InsertFixuper.h"
#include "RBTree.h"
#include <gtest/gtest.h>

class InsertFixuper_fixture : public testing::Test
{
protected:
    std::shared_ptr<Node>& getRoot()
    {
        return tree.root;
    }

    RBTree tree;
};

TEST_F(InsertFixuper_fixture, LeftLeft)
{
    auto& root = getRoot();
    root = std::make_shared<Node>(Node{.value = 10, .color = NodeColor::black});
    root->left = std::make_shared<Node>(
        Node{.value = 5, .parent = root, .color = NodeColor::red});
    root->left->left = std::make_shared<Node>(
        Node{.value = 2, .parent = root->left, .color = NodeColor::red});

    InsertFixuper fixuper(tree);
    fixuper.FixUp(root->left->left);

    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->left->value, 2);
    EXPECT_EQ(root->right->value, 10);
}

TEST_F(InsertFixuper_fixture, LeftRight)
{
    auto& root = getRoot();
    root = std::make_shared<Node>(Node{.value = 10, .color = NodeColor::black});
    root->left = std::make_shared<Node>(
        Node{.value = 5, .parent = root, .color = NodeColor::red});
    root->left->right = std::make_shared<Node>(
        Node{.value = 7, .parent = root->left, .color = NodeColor::red});

    InsertFixuper fixuper(tree);
    fixuper.FixUp(root->left->right);

    EXPECT_EQ(root->value, 7);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->right->value, 10);
}

TEST_F(InsertFixuper_fixture, RightLeft)
{
    auto& root = getRoot();
    root = std::make_shared<Node>(Node{.value = 10, .color = NodeColor::black});
    root->right = std::make_shared<Node>(
        Node{.value = 15, .parent = root, .color = NodeColor::red});
    root->right->left = std::make_shared<Node>(
        Node{.value = 12, .parent = root->right, .color = NodeColor::red});

    InsertFixuper fixuper(tree);
    fixuper.FixUp(root->right->left);

    EXPECT_EQ(root->value, 12);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 15);
}

TEST_F(InsertFixuper_fixture, RightRight)
{
    auto& root = getRoot();
    root = std::make_shared<Node>(Node{.value = 10, .color = NodeColor::black});
    root->right = std::make_shared<Node>(
        Node{.value = 15, .parent = root, .color = NodeColor::red});
    root->right->right = std::make_shared<Node>(
        Node{.value = 20, .parent = root->right, .color = NodeColor::red});

    InsertFixuper fixuper(tree);
    fixuper.FixUp(root->right->right);

    EXPECT_EQ(root->value, 15);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 20);
}

TEST_F(InsertFixuper_fixture, RedUncle)
{
    auto& root = getRoot();
    root = std::make_shared<Node>(Node{.value = 10, .color = NodeColor::black});
    root->left = std::make_shared<Node>(
        Node{.value = 5, .parent = root, .color = NodeColor::red});
    root->right = std::make_shared<Node>(
        Node{.value = 15, .parent = root, .color = NodeColor::red});
    root->right->right = std::make_shared<Node>(
        Node{.value = 20, .parent = root->right, .color = NodeColor::red});

    InsertFixuper fixuper(tree);
    fixuper.FixUp(root->right->right);

    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->right->value, 15);
    EXPECT_EQ(root->right->right->value, 20);
    EXPECT_EQ(root->color, NodeColor::black);
    EXPECT_EQ(root->left->color, NodeColor::black);
    EXPECT_EQ(root->right->color, NodeColor::black);
    EXPECT_EQ(root->right->right->color, NodeColor::red);
}
