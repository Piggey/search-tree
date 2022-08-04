#pragma once

#include <vector>
#include <string>

namespace st
{
struct TreeNode;

class Tree
{

public:
    /**
     * @brief initializes an empty Tree object.
     */
    Tree();

    /**
     * @brief initializes a Tree object with provided list of words
     * @param wordlist: vector of words to be put inside a Tree
     */
    explicit Tree(const std::vector<std::string>& wordlist);

    /**
     * @brief Tree object deconstructor. Deletes all TreeNodes inside of a Tree.
     */
    ~Tree();

    /**
     * @brief puts a word into a Tree
     * @param word: word to be put
     */
    void put(const std::string& word);

    /**
     * @brief remove a word from a Tree
     * does nothing when word is not in a Tree
     * @param word: word to be removed
     */
    void remove(const std::string& word);

    /**
     * @brief find all words with provided prefix
     * @param prefix: first characters of a word
     * @param ignore_case_sens: option to be case-insensitive. Set to false by default.
     * @attention function returns empty vector when nothing was found
     * @return a list of all words with provided prefix in a Tree
     */
    std::vector<std::string> find(std::string prefix, bool ignore_case_sens = false) const;

    /**
     * @brief number of words currently stored in a Tree
     * @return size
     */
    size_t size() const;

private: // fields
    TreeNode* m_root;
    size_t m_size;
};
}
