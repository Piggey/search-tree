#ifndef SEARCH_TREE_TREE_H
#define SEARCH_TREE_TREE_H

#include "TreeNode.h"

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
    explicit Tree(const std::vector<std::string>& wordlist);

    /**
     * @brief put a word into a Tree
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
     * @attention function returns empty vector when nothing was found
     * @return a list of all words with provided prefix in a Tree
     */
    std::vector<std::string> find(std::string prefix) const;

    /**
     * @brief number of words currently stored in a Tree
     * @return size
     */
    size_t size() const;

    /**
     * @brief get the pointer of the root TreeNode
     * @return pointer to an immutable root node object
     */
    const TreeNode* root() const;

    ~Tree();

private: // fields
    TreeNode m_root;
    size_t m_size;
};

#endif //SEARCH_TREE_TREE_H
