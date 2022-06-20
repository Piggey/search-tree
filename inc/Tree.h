#ifndef SEARCH_TREE_TREE_H
#define SEARCH_TREE_TREE_H

#include <vector>
#include <string>

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
    explicit Tree(std::vector<std::string> wordlist);

    /**
     * @brief put a word into a Tree
     * @param word: word to be put
     */
    void put(std::string word);

    /**
     * @brief find all words with provided prefix
     * @param prefix: first characters of a word
     * @return a list of all words with provided prefix in a Tree
     */
    std::vector<std::string> find(std::string prefix);

    /**
     * @brief number of words currently stored in a Tree
     * @return size
     */
    size_t size();
    virtual ~Tree();

private: // functions
    int check_node_exists(TreeNode* parent, char c);

private: // fields
    TreeNode* m_root;
    size_t m_size;
};

// structure of a single tree node
struct TreeNode
{
    // todo: make it work for utf-8 characters too
    char c;                             // single character
    std::vector<TreeNode*> children;    // list of pointers to all children nodes
};

#endif //SEARCH_TREE_TREE_H
