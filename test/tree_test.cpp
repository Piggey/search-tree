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
    EXPECT_EQ(t.size(), 2);

    t.remove("kretyn");
    EXPECT_EQ(t.size(), 1);
    EXPECT_EQ(t.find("kr")[0], "kreyoei");

    // try to remove the same word
    t.remove("kretyn");
    EXPECT_EQ(t.size(), 1);
    EXPECT_EQ(t.find("kr")[0], "kreyoei");

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
    Tree t({ "foo", "bar", "bara", "bare", "baz", "fizz", "buzz", "fizzbuzz" });

    // normal search
    std::vector<std::string> found = t.find("b"); // bar, baz, bara, bare
    std::vector<std::string> correct = { "bar", "bara", "bare", "baz" };

    EXPECT_EQ(found.size(), 4);
    for (unsigned int i = 0; i < found.size(); i++)
        EXPECT_EQ(found[i], correct[i]);

    // prefix whole word
    found = t.find("fizzbuzz"); // fizzbuzz
    EXPECT_EQ(found.size(), 1);
    EXPECT_EQ(found[0], "fizzbuzz");

    // search for a word that doesnt exist in Tree
    found = t.find("abcd");
    EXPECT_EQ(found.size(), 0);

    // search with empty string
    found = t.find("");
    EXPECT_EQ(found.size(), 8);

    correct = { "foo", "fizz", "fizzbuzz", "bar", "bara", "bare", "baz", "buzz" };
    for(unsigned int i = 0; i < correct.size(); i++)
        EXPECT_EQ(found[i], correct[i]);

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

    auto found = t.find("fizzb", true);
    EXPECT_EQ(found.size(), 3);
    EXPECT_EQ(found[0], "fizzbuzz");
    EXPECT_EQ(found[1], "fizzBUZZ");
    EXPECT_EQ(found[2], "FIZZBUZZ");

    // 'FIZZBUZZ' first since its the most similar to the prefix
    found = t.find("FIZZB", true);
    EXPECT_EQ(found.size(), 3);
    EXPECT_EQ(found[0], "FIZZBUZZ");

    // just checking whether it gets checked only on letters
    found = t.find(";", true);
    EXPECT_EQ(found.size(), 0);

    found = t.find("{", true);
    EXPECT_EQ(found.size(), 0);

    // empty string as prefix
    found = t.find("", true);
    std::vector<std::string> correct = { "fiZZ", "fizzBUZZ", "fizzbuzz", "FIZZBUZZ", "[]square" };

    EXPECT_EQ(found.size(), 5);
    for (unsigned int i = 0; i < found.size(); i++)
        EXPECT_EQ(found[i], correct[i]);
}
