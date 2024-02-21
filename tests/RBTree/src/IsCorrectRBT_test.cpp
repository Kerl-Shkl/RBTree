#include "IsCorrectRBT.h"
#include "RBTree.h"
#include <gtest/gtest.h>

TEST(IsCorrectRBT, Correct)
{
    auto root =
        std::make_shared<Node>(Node{.value = 26, .color = NodeColor::black});
    auto l = std::make_shared<Node>(Node{.value = 17, .color = NodeColor::red});
    auto r =
        std::make_shared<Node>(Node{.value = 41, .color = NodeColor::black});
    auto ll =
        std::make_shared<Node>(Node{.value = 14, .color = NodeColor::black});
    auto lr =
        std::make_shared<Node>(Node{.value = 21, .color = NodeColor::black});
    auto rl =
        std::make_shared<Node>(Node{.value = 30, .color = NodeColor::red});

    root->left = l;
    root->right = r;
    r->left = rl;
    l->left = ll;
    l->right = lr;
    RBTree tree;
    tree.root = root;

    EXPECT_TRUE(isRBTreeCorrect(tree));
}

TEST(IsCorrectRBT, RedRoot)
{
    auto root =
        std::make_shared<Node>(Node{.value = 26, .color = NodeColor::red});
    auto l =
        std::make_shared<Node>(Node{.value = 17, .color = NodeColor::black});
    auto r =
        std::make_shared<Node>(Node{.value = 41, .color = NodeColor::black});

    root->left = l;
    root->right = r;
    RBTree tree;
    tree.root = root;

    EXPECT_FALSE(isRBTreeCorrect(tree));
}

TEST(IsCorrectRBT, DiffBlackQuantities)
{
    auto root =
        std::make_shared<Node>(Node{.value = 26, .color = NodeColor::black});
    auto l = std::make_shared<Node>(Node{.value = 17, .color = NodeColor::red});
    auto r =
        std::make_shared<Node>(Node{.value = 41, .color = NodeColor::black});
    auto ll =
        std::make_shared<Node>(Node{.value = 14, .color = NodeColor::black});
    auto lr =
        std::make_shared<Node>(Node{.value = 21, .color = NodeColor::black});
    auto rl =
        std::make_shared<Node>(Node{.value = 30, .color = NodeColor::black});

    root->left = l;
    root->right = r;
    r->left = rl;
    l->left = ll;
    l->right = lr;
    RBTree tree;
    tree.root = root;

    EXPECT_FALSE(isRBTreeCorrect(tree));
}

TEST(IsCorrectRBT, IncorrectOrder)
{
    auto root =
        std::make_shared<Node>(Node{.value = 26, .color = NodeColor::black});
    auto l = std::make_shared<Node>(Node{.value = 17, .color = NodeColor::red});
    auto r =
        std::make_shared<Node>(Node{.value = 41, .color = NodeColor::black});
    auto ll =
        std::make_shared<Node>(Node{.value = 14, .color = NodeColor::black});
    auto lr =
        std::make_shared<Node>(Node{.value = 21, .color = NodeColor::black});
    auto rl =
        std::make_shared<Node>(Node{.value = 50, .color = NodeColor::black});

    root->left = l;
    root->right = r;
    r->left = rl;
    l->left = ll;
    l->right = lr;
    RBTree tree;
    tree.root = root;

    EXPECT_FALSE(isRBTreeCorrect(tree));
}

TEST(IsCorrectRBT, empty)
{
    RBTree tree;

    EXPECT_TRUE(isRBTreeCorrect(tree));
}
