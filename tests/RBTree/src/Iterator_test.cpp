#include "RBTreeRefactor.h"
#include <gtest/gtest.h>

TEST(Iterator, Sorted)
{
    std::vector<int> source{91, 34, 27, 4, 104, 74};
    RBTreeRefactor tree;
    for (int i : source) {
        tree.Insert(i);
    }

    std::vector<int> dest;
    std::copy(tree.begin(), tree.end(), std::back_inserter(dest));

    ASSERT_EQ(tree.Size(), source.size());
    ASSERT_EQ(dest.size(), tree.Size());
    EXPECT_TRUE(std::is_sorted(dest.begin(), dest.end()));
    EXPECT_TRUE(std::is_permutation(dest.begin(), dest.end(), source.begin(),
                                    source.end()));
}

TEST(Iterator, ReverseBypass)
{
    RBTreeRefactor tree;
    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(4);
    tree.Insert(5);

    for (auto it = tree.begin(), jt = ++tree.begin(); jt != tree.end();
         ++it, ++jt)
    {
        auto temp = jt;
        EXPECT_EQ(it, --temp);
    }
}
