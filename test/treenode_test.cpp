#include "gtest/gtest.h"
#include "TreeNode.h"

#include <vector>

TEST(tree_node_class_test, constructor)
{
    TreeNode tn;
    EXPECT_EQ(tn.children.size(), 0);
}