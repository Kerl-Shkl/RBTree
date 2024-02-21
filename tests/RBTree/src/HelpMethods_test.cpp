#include "RBTreeRefactor.h"
#include <gtest/gtest.h>

TEST(Empty, EmptyTree)
{
    RBTreeRefactor tree;
    EXPECT_TRUE(tree.Empty());
}

TEST(Empty, NotEmptyTree)
{
    RBTreeRefactor tree;
    tree.Insert(10);
    EXPECT_FALSE(tree.Empty());
}

TEST(Size, EmptyTree)
{
    RBTreeRefactor tree;
    EXPECT_EQ(tree.Size(), 0);
}

TEST(Size, NotEmptyTree)
{
    RBTreeRefactor tree;
    tree.Insert(10);
    tree.Insert(15);
    tree.Insert(16);
    tree.Insert(17);
    EXPECT_EQ(tree.Size(), 4);
}

TEST(Find, MustFind)
{
    RBTreeRefactor tree;
    tree.Insert(10);
    tree.Insert(15);
    tree.Insert(16);
    tree.Insert(17);

    auto it = tree.Find(16);

    EXPECT_EQ(*it, 16);
}

TEST(Find, MustNotFind)
{
    RBTreeRefactor tree;
    tree.Insert(10);
    tree.Insert(15);
    tree.Insert(16);
    tree.Insert(17);

    auto it = tree.Find(18);

    EXPECT_EQ(it, tree.end());
}
