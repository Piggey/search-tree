#include "Tree.h"
#include "logger.h"

#include <stack>

/**
 * @brief check whether parent node has a child with char c
 * @param parent: parent Tree node
 * @param c: character to be checked
 * @attention this function returns -1 when child node was NOT found
 * @return index of child with char c, or -1 when not found
 */
int check_node_exists(const TreeNode* parent, char c);

Tree::Tree()
{
    m_root.c = 0;
    m_size = 0;
    LOG_INFO("new Tree object created");
}

Tree::Tree(const std::vector<std::string>& wordlist)
{
    m_root.c = 0;
    m_size = 0;

    for (const std::string& word: wordlist)
        if (!word.empty()) put(word);

    LOG_INFO("new Tree object created with provided wordlist");
}

void Tree::put(const std::string& word)
{
    // store the node we're putting a new node into
    // starting from root
    TreeNode* current = &m_root;

    // this prevents incrementing m_size
    // when 2 same words will be provided
    bool node_created = false;

    for (char c : word)
    {
        // check if there is a node with this character
        int child_node_index = check_node_exists(current, c);

        if (child_node_index == -1) // does not exist
        {
            // create and add a new one
            current->children.emplace_back(c);
            node_created = true;

            // move into the child
            current = &current->children[current->children.size() - 1];
        }
        else // node already exists
        {
            current = &current->children[child_node_index];
        }
    }

    if (!node_created && current->eow)
    {
        LOG_WARN("tried to put word that was already in a Tree");
        return; // user put 2 same words
    }

    m_size++;
    current->eow = true;
    LOG_INFO("new word inserted into Tree");
}

void Tree::remove(const std::string& word)
{
    // todo: to be implemented
}

std::vector<std::string> Tree::find(std::string prefix)
{
    std::vector<std::string> out; // list of found words
    TreeNode* current = &m_root;

    // go through the nodes from the prefix, if they exist
    for (char c : prefix)
    {
        int child_index = check_node_exists(current, c);
        if (child_index == -1)
            return out; // there arent any words with that prefix

        current = &current->children[child_index];
    }

    std::string word = prefix;
    std::stack<TreeNode*> stack; // dfs stack

    // in case provided prefix is already a word
    if (current->eow)
        out.push_back(word);

    // push children nodes to stack
    for (auto& child : current->children)
        stack.push(&child);

    while (!stack.empty())
    {
        current = stack.top(); stack.pop();
        word += current->c;

        if (current->eow)
        {
            out.push_back(word);
            LOG_INFO("word found");

            if (current->children.size() == 0)
                word = prefix;
        }

        if (current->children.size() > 1)
            // since we will be coming back to this node
            prefix += current->c;

        for (auto& child : current->children)
            stack.push(&child);
    }

    return out;
}

size_t Tree::size() const
{
    return m_size;
}

Tree::~Tree()
{
    // todo: free the memory from all the TreeNodes
}

int check_node_exists(const TreeNode* parent, char c)
{
    for (int i = 0; i < parent->children.size(); i++)
    {
        if (parent->children[i].c == c)
            return i;
    }

    return -1;
}
