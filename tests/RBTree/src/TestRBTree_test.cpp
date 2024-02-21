#include "TestRBTree.h"
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
    TestRBTree tree;
    tree.getRoot() = root;

    EXPECT_TRUE(tree.IsTreeCorrect());
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
    TestRBTree tree;
    tree.getRoot() = root;

    EXPECT_FALSE(tree.IsTreeCorrect());
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
    TestRBTree tree;
    tree.getRoot() = root;

    EXPECT_FALSE(tree.IsTreeCorrect());
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
    TestRBTree tree;
    tree.getRoot() = root;

    EXPECT_FALSE(tree.IsTreeCorrect());
}

TEST(IsCorrectRBT, empty)
{
    TestRBTree tree;

    EXPECT_TRUE(tree.IsTreeCorrect());
}
