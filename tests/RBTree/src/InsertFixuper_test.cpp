#include "InsertFixuper.h"
#include "RBTreeRefactor.h"
#include <gtest/gtest.h>

class OpenedRBTree : public RBTreeRefactor
{
public:
    using RBTreeRefactor::getRoot;
};

TEST(InsertFixuperTest, LeftLeft)
{
    OpenedRBTree tree;
    auto& root = tree.getRoot();

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

TEST(InsertFixuperTest, LeftRight)
{
    OpenedRBTree tree;
    auto& root = tree.getRoot();
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

TEST(InsertFixuperTest, RightLeft)
{
    OpenedRBTree tree;
    auto& root = tree.getRoot();
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

TEST(InsertFixuperTest, RightRight)
{
    OpenedRBTree tree;
    auto& root = tree.getRoot();
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

TEST(InsertFixuperTest, RedUncle)
{
    OpenedRBTree tree;
    auto& root = tree.getRoot();
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
