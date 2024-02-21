#include "IsCorrectRBT.h"
#include "RBTree.h"
#include <gtest/gtest.h>

class Delete_fixture : public testing::Test
{
protected:
    void SetUp() override
    {
        tree.Insert(26);
        tree.Insert(17);
        tree.Insert(41);
        tree.Insert(14);
        tree.Insert(21);
        tree.Insert(30);
        tree.Insert(47);
        tree.Insert(10);
        tree.Insert(16);
        tree.Insert(19);
        tree.Insert(23);
        tree.Insert(28);
        tree.Insert(38);
        tree.Insert(7);
        tree.Insert(12);
        tree.Insert(15);
        tree.Insert(20);
        tree.Insert(35);
        tree.Insert(39);
        tree.Insert(3);
    }

    RBTree tree;
};

TEST_F(Delete_fixture, FromLeft)
{
    auto left = tree.root->left->left;
    ASSERT_TRUE(isRBTreeCorrect(tree));
    ASSERT_NE(left, nullptr);

    tree.Delete(left);

    EXPECT_TRUE(isRBTreeCorrect(tree));
    EXPECT_NE(tree.root->left->left, left);
}
