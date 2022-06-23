#include "gtest/gtest.h"
#include "Tree.h"

#include <vector>
#include <string>

TEST(tree_class_test, constuctors)
{
    // init empty Tree
    Tree t;
    EXPECT_EQ(t.size(), 0);

    // init Tree with words list
    std::vector<std::string> sample_words { "widePeepoHappy", "widePeepoSad" };
    Tree t2(sample_words);
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

TEST(tree_class_test, find)
{
    std::vector<std::string> wordlist { "foo", "bar", "baz", "fizz", "buzz", "fizzbuzz" };
    Tree t(wordlist);

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

    // search in an empty Tree
    Tree t2;
    found = t2.find("");
    EXPECT_EQ(found.size(), 0);

}
