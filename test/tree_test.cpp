#include <gtest/gtest.h>
#include "../search-tree/TreeNode.h"
#include "../search-tree/Tree.h"

#include <vector>
#include <string>

using st::Tree;
using st::TreeNode;

TEST(tree_class_test, constuctors)
{
    // init empty Tree
    Tree t;
    EXPECT_EQ(t.size(), 0);

    // init Tree with words list
    Tree t2({ "widePeepoHappy", "widePeepoSad" });

    EXPECT_EQ(t2.size(), 2);
}

TEST(tree_class_test, put)
{
    Tree t;
    t.put("Kappa");
    EXPECT_EQ(t.size(), 1);

    t.put("Kapr");
    EXPECT_EQ(t.size(), 2);

    // try to put the same word in
    t.put("Kapr");
    EXPECT_EQ(t.size(), 2);
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

    // normal remove() use case
    EXPECT_EQ(t.find("kr").size(), 2);

    t.remove("kretyn");
    EXPECT_EQ(t.find("kr").size(), 1);

    EXPECT_EQ(t.find("kr")[0], "kreyoei");

    // try to remove the same word
    t.remove("kretyn");
    EXPECT_EQ(t.find("kr").size(), 1);

    // try to remove word that's nested inside another word
    // (don't delete any nodes, but decrement word counter)
    t.put("kretyn");
    t.put("kretynka");

    EXPECT_EQ(t.size(), 3);
    t.remove("kretyn");
    EXPECT_EQ(t.size(), 2);

    auto found = t.find("kr");
    EXPECT_EQ(found[0], "kreyoei");
    EXPECT_EQ(found[1], "kretynka");
}

TEST(tree_class_test, find)
{
    Tree t({ "foo", "bar", "baz", "fizz", "buzz", "fizzbuzz" });

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

TEST(tree_class_test, find_case_insensitive)
{
    Tree t({ "fiZZ", "fizzBUZZ", "fizzbuzz", "FIZZBUZZ", "[]square" });

    auto found = t.find("fizzbuzz", true);
    EXPECT_EQ(found.size(), 3);
    EXPECT_EQ(found[0], "fizzbuzz");
    EXPECT_EQ(found[1], "fizzBUZZ");
    EXPECT_EQ(found[2], "FIZZBUZZ");

    // just checking whether it gets checked only on letters
    found = t.find(";", true);
    EXPECT_EQ(found.size(), 0);

    found = t.find("{", true);
    EXPECT_EQ(found.size(), 0);

    // empty string as prefix
    found = t.find("", true); // FIXME: these are NOT correct values! (not the problem with ignoring case sens i think)
    EXPECT_EQ(found.size(), 5);
}
