#include "RBTree.h"
#include <gtest/gtest.h>

class RBTree_fixture : public testing::Test
{
protected:
    std::shared_ptr<Node>& getRoot()
    {
        return tree.root;
    }

    RBTree tree;
};

TEST_F(RBTree_fixture, InsertWithFixup)
{
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(2);

    EXPECT_EQ(tree.root->value, 5);
    EXPECT_EQ(tree.root->left->value, 2);
    EXPECT_EQ(tree.root->right->value, 10);
}

TEST_F(RBTree_fixture, InsertWithoutFixup)
{
    tree.Insert(5);
    tree.Insert(10);
    tree.Insert(2);

    EXPECT_EQ(tree.root->value, 5);
    EXPECT_EQ(tree.root->left->value, 2);
    EXPECT_EQ(tree.root->right->value, 10);
}
