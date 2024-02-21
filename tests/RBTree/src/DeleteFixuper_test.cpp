#include "DeleteFixuper.h"
#include "IsCorrectRBT.h"
#include "RBTree.h"
#include <gtest/gtest.h>

class RBTree_fixture : public testing::Test
{
protected:
    void SetUp() override
    {}

    std::shared_ptr<Node>& getRoot()
    {
        return tree.root;
    }

    RBTree tree;
};

// TEST_F(RBTree_fixture, DeleteFixuperTest)
// {
//     auto root = std::make_shared<Node>(Node{.value})
// }
