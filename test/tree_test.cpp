#include <gtest/gtest.h>
#include "../search-tree/TreeNode.h"
#include "../search-tree/Tree.h"

#include <vector>
#include <string>
#include <queue>

using st::Tree;
using st::TreeNode;

/**
 * @brief get the count of nodes currently used by the Tree
 * @param tree: Tree object pointer we want to check
 * @return count of the nodes (with root node!)
 */
int get_tree_node_count(const Tree* tree);

TEST(tree_class_test, constuctors)
{
    // init empty Tree
    Tree t;
    EXPECT_EQ(t.size(), 0);
    EXPECT_EQ(get_tree_node_count(&t), 1);

    // init Tree with words list
    Tree t2({ "widePeepoHappy", "widePeepoSad" });

    EXPECT_EQ(t2.size(), 2);
    EXPECT_EQ(get_tree_node_count(&t2), 1 + 9 + 5 + 3);
}

TEST(tree_class_test, put)
{
    Tree t;
    t.put("Kappa");
    EXPECT_EQ(t.size(), 1);
    EXPECT_EQ(get_tree_node_count(&t), 1 + 5);

    t.put("Kapr");
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(get_tree_node_count(&t), 1 + 5 + 1);

    // try to put the same word in
    t.put("Kapr");
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(get_tree_node_count(&t), 1 + 5 + 1);
}

TEST(tree_class_test, remove)
{
    Tree t;

    // remove from empty Tree
    EXPECT_EQ(t.size(), 0);
    t.remove("nonexistent_word");
    EXPECT_EQ(t.size(), 0);

    t.put("kretyn");
    t.put("kreyoei");

    EXPECT_EQ(get_tree_node_count(&t), 1 + 6 + 4);

    // normal remove() use case
    EXPECT_EQ(t.find("kr").size(), 2);

    t.remove("kretyn");
    EXPECT_EQ(t.find("kr").size(), 1);

    EXPECT_EQ(t.find("kr")[0], "kreyoei");

    EXPECT_EQ(get_tree_node_count(&t), 1 + 6 + 4 - 3);

    // try to remove the same word
    t.remove("kretyn");
    EXPECT_EQ(t.find("kr").size(), 1);
    EXPECT_EQ(get_tree_node_count(&t), 1 + 6 + 4 - 3);


    // try to remove word that's nested inside another word
    // (don't delete any nodes, but decrement word counter)
    t.put("kretyn");
    t.put("kretynka");
    EXPECT_EQ(get_tree_node_count(&t), 1 + 6 + 4 + 2);

    EXPECT_EQ(t.size(), 3);
    t.remove("kretyn");
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(get_tree_node_count(&t), 1 + 6 + 4 + 2);

    auto found = t.find("kr");
    EXPECT_EQ(found[0], "kreyoei");
    EXPECT_EQ(found[1], "kretynka");
}

TEST(tree_class_test, find)
{
    Tree t({ "foo", "bar", "baz", "fizz", "buzz", "fizzbuzz" });
    EXPECT_EQ(get_tree_node_count(&t), 1 + 3 + 3 + 1 + 3 + 3 + 4);

    // normal search
    std::vector<std::string> found = t.find("ba"); // bar, baz
    EXPECT_EQ(found.size(), 2);
    EXPECT_EQ(found[0], "bar");
    EXPECT_EQ(found[1], "baz");

    // prefix whole word
    found = t.find("fizzbuzz"); // fizzbuzz
    EXPECT_EQ(found.size(), 1);
    EXPECT_EQ(found[0], "fizzbuzz");

    // search for a word that doesnt exist in Tree
    found = t.find("abcd");
    EXPECT_EQ(found.size(), 0);

    // search with empty string
    found = t.find("");
    EXPECT_EQ(found.size(), 6);

    // search something longer than existing word
    found = t.find("barz");
    EXPECT_EQ(found.size(), 0);

    // search in an empty Tree
    Tree t2;
    found = t2.find("");
    EXPECT_EQ(found.size(), 0);
}

int get_tree_node_count(const Tree* tree)
{
    int counter = 0;
    std::queue<const TreeNode*> q;

    q.push(tree->root());
    counter++; // should i even consider a root node as a node?

    while (!q.empty())
    {
        const TreeNode* node = q.front(); q.pop();

        for (const auto& child : node->children)
        {
            q.push(child);
            counter++;
        }
    }

    return counter;
}
