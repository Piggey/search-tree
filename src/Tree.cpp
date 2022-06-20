#include "Tree.h"

Tree::Tree()
{
    m_root = new TreeNode;
    m_root->c = 0;
    m_size = 0;
}

Tree::Tree(std::vector<std::string> wordlist)
{
    m_root = new TreeNode;
    m_root->c = 0;
    m_size = 0;

    for (std::string word : wordlist)
    {
        // todo: log on error
        // logging in general lol
        put(word);
    }
}

void Tree::put(std::string word)
{
    // store the node we're putting a new node into
    // starting from root
    TreeNode* parent_node = m_root;

    for (char c : word)
    {
        // check if there is a node with this character
        int child_node_index = check_node_exists(parent_node, c);

        if (child_node_index == -1) // does not exist
        {
            // create and add a new one
            TreeNode node;
            node.c = c;

            // move into the created node
            parent_node->children.push_back(&node);
        }
        else // node already exists
        {
            parent_node = parent_node->children[child_node_index];
        }
    }

    m_size++;
}

std::vector<std::string> Tree::find(std::string prefix)
{
    return std::vector<std::string>();
}

size_t Tree::size()
{
    return m_size;
}

Tree::~Tree()
{
    delete m_root;
}

int Tree::check_node_exists(TreeNode *parent, char c)
{
    for (int i = 0; i < parent->children.size(); i++)
    {
        if (parent->children[i]->c == c)
        {
            return i;
        }
    }

    return -1;
}
