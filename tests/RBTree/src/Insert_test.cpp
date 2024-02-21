#include "RBTreeRefactor.h"
#include "TestRBTree.h"
#include <gtest/gtest.h>

TEST(InsertTest, isRBTreeCorrect)
{
    TestRBTree tree;
    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(10);
    tree.Insert(13);
    tree.Insert(2);
    tree.Insert(3);

    ASSERT_TRUE(tree.IsTreeCorrect());
}

TEST(InsertTest, InsertWithFixup)
{
    TestRBTree tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(2);

    auto& root = tree.getRoot();
    ASSERT_TRUE(tree.IsTreeCorrect());
    EXPECT_EQ(tree.Size(), 3);
    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->left->value, 2);
    EXPECT_EQ(root->right->value, 10);
}

TEST(InsertTest, InsertWithoutFixup)
{
    TestRBTree tree;
    tree.Insert(5);
    tree.Insert(10);
    tree.Insert(2);

    auto& root = tree.getRoot();
    ASSERT_TRUE(tree.IsTreeCorrect());
    EXPECT_EQ(tree.Size(), 3);
    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->left->value, 2);
    EXPECT_EQ(root->right->value, 10);
}
