#include "gtest/gtest.h"
#include "../search_tree/TreeNode.h"

#include <vector>

TEST(tree_node_class_test, constructor)
{
    st::TreeNode tn;
    EXPECT_EQ(tn.children.size(), 0);
    EXPECT_FALSE(tn.eow);
}