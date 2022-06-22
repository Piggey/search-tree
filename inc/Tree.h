#ifndef SEARCH_TREE_TREE_H
#define SEARCH_TREE_TREE_H

#include "TreeNode.h"

#include <vector>
#include <string>

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
    Tree(const std::vector<std::string>& wordlist);

    /**
     * @brief put a word into a Tree
     * @param word: word to be put
     */
    void put(const std::string& word);

    /**
     * @brief find all words with provided prefix
     * @param prefix: first characters of a word
     * @attention the end of the word is signaled by adding a nullptr node to the last character node
     * at the first position of list of children
     * @return a list of all words with provided prefix in a Tree
     */
    std::vector<std::string> find(const std::string& prefix);

    /**
     * @brief number of words currently stored in a Tree
     * @return size
     */
    size_t size() const;

    ~Tree();

private: // fields
    TreeNode m_root;
    size_t m_size;
};

#endif //SEARCH_TREE_TREE_H
