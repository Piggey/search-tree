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
    std::vector<std::string> wordlist { "Kappa", "Kappar", "Krey", "Kretyn" };
    Tree t(wordlist);


    std::vector<std::string> found = t.find("Kr"); // Kretyn, Krey
    for (int i = 0; i < found.size(); i++)
    {
        std::cout << found[i] << "\n";
    }

    found = t.find("Kappa"); // Kappa, Kappar
    for (int i = 0; i < found.size(); i++)
    {
        std::cout << found[i] << "\n";
    }

    wordlist = {"abd", "abe", "acf", "acg"};
    Tree t2(wordlist);
    found = t2.find("a");
    for (int i = 0; i < found.size(); i++)
    {
        std::cout << found[i] << "\n";
    }
}
