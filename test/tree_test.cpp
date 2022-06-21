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

