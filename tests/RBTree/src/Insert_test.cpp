#include "IsCorrectRBT.h"
#include "RBTreeRefactor.h"
#include <gtest/gtest.h>

class OpenedRBTree : public RBTreeRefactor
{
public:
    using RBTreeRefactor::getRoot;
};

TEST(InsertTest, InsertWithFixup)
{
    OpenedRBTree tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(2);

    auto& root = tree.getRoot();
    EXPECT_EQ(tree.Size(), 3);
    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->left->value, 2);
    EXPECT_EQ(root->right->value, 10);
}

TEST(InsertTest, InsertWithoutFixup)
{
    OpenedRBTree tree;
    tree.Insert(5);
    tree.Insert(10);
    tree.Insert(2);

    auto& root = tree.getRoot();
    EXPECT_EQ(tree.Size(), 3);
    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->left->value, 2);
    EXPECT_EQ(root->right->value, 10);
}

// TEST_F(RBTree_fixture, isRBTreeCorrect_test)
// {
//     tree.Insert(5);
//     tree.Insert(7);
//     tree.Insert(10);
//     tree.Insert(13);
//     tree.Insert(2);
//     tree.Insert(3);
//
//     EXPECT_TRUE(isRBTreeCorrect(tree));
// }
