#include <iostream>
#include "Tree.h"
#include "logger.h"

Tree::Tree()
{
    m_root.c = 0;
    m_size = 0;
}

Tree::Tree(const std::vector<std::string>& wordlist)
{
    std::cout << "ty no to sie odpala teraz nie\n";
    m_root.c = 0;
    m_size = 0;

    for (const std::string& word: wordlist)
        if (!word.empty()) put(word);

    LOG_INFO("new Tree object created with provided wordlist");
}

void Tree::put(const std::string& word)
{
    LOG_INFO("putting word into Tree")

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
            TreeNode node;
            node.c = c;

            // move into the created node
            current->children.push_back(&node);

            node_created = true;
        }
        else // node already exists
        {
            current = current->children[child_node_index];
        }
    }

    if (!node_created && current->children[0] == nullptr)
    {
        LOG_WARN("tried to put word that was already in a Tree");
        return; // user put 2 same words
    }

    // signal end of word
    current->children.insert(current->children.begin(), nullptr);
    m_size++;
    LOG_INFO("new word inserted into Tree");
}

std::vector<std::string> Tree::find(const std::string& prefix)
{
    std::vector<std::string> out;
    TreeNode* current = &m_root;

    // go through the nodes from the prefix, if they exist
    for (char c : prefix)
    {
        int child_index = check_node_exists(current, c);

        if (child_index == -1)
            return out; // there arent any words with that prefix

        current = current->children[child_index];
    }

    // basically DFS through the nodes
    return out;
}

size_t Tree::size() const
{
    return m_size;
}

int Tree::check_node_exists(TreeNode* parent, char c)
{
    for (int i = 0; i < parent->children.size(); i++)
    {
        // skip end of word signal
        if (parent->children[i] == nullptr)
            continue;

        if (parent->children[i]->c == c)
            return i;
    }

    return -1;
}
