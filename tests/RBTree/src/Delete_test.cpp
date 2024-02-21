#include "TestRBTree.h"
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
        ASSERT_TRUE(tree.IsTreeCorrect());
    }

    TestRBTree tree;
};

TEST_F(Delete_fixture, FromLeft)
{
    auto left = tree.getRoot()->left->left;
    ASSERT_NE(left, nullptr);

    int old_size = tree.Size();
    int value = left->value;
    auto it = tree.Find(value);
    auto expected_new_it = it;
    ++expected_new_it;

    auto new_it = tree.Delete(it);

    EXPECT_TRUE(tree.IsTreeCorrect());
    EXPECT_EQ(old_size, tree.Size() + 1);
    EXPECT_FALSE(tree.Contain(value));
    EXPECT_EQ(*new_it, *expected_new_it);
}

TEST_F(Delete_fixture, FromRoot)
{
    int old_size = tree.Size();
    int value = tree.getRoot()->value;
    auto it = tree.Find(value);
    auto expected_new_it = it;
    ++expected_new_it;

    auto new_it = tree.Delete(it);

    EXPECT_TRUE(tree.IsTreeCorrect());
    EXPECT_EQ(old_size, tree.Size() + 1);
    EXPECT_FALSE(tree.Contain(value));
    EXPECT_EQ(*new_it, *expected_new_it);
}
