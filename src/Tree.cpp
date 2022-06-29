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
    if (m_size == 0)
    {
        LOG_WARN("tried to remove a word from an empty Tree");
        return;
    }

    TreeNode* current = &m_root;

    // keep the parent node and child index of the node we want to delete
    // stack since we want to delete them bottom up
    std::stack<std::pair<TreeNode*, int>> to_be_deleted;

    // collect the nodes that will be deleted
    for (int i = 0; i < word.size(); i++)
    {
        char c = word[i];
        int child_index = check_node_exists(current, c);

        // word doesnt exist in a Tree
        if (child_index == -1)
        {
            LOG_WARN("tried to remove a word that did not exist in a Tree");
            return;
        }

        // one word is using current node
        if (find(word.substr(0, i + 1)).size() <= 1)
        {
            to_be_deleted.push(std::make_pair(current, child_index));
        }

        current = &current->children[child_index];
    }

    current->eow = false;   // unset the end of word flag on the last node (if was used)
    m_size--;               // decrement words counter

    // delete the nodes
    while (!to_be_deleted.empty())
    {
        auto pair = to_be_deleted.top(); to_be_deleted.pop();
        auto pos = pair.first->children.begin() + pair.second;
        pair.first->children.erase(pos);
    }
}

std::vector<std::string> Tree::find(std::string prefix) const
{
    std::vector<std::string> out; // list of found words
    const TreeNode* current = &m_root;

    // empty Tree case
    if (m_size == 0)
    {
        LOG_WARN("tried to search an empty Tree.");
        return out;
    }

    // go through the nodes from the prefix, if they exist
    for (char c : prefix)
    {
        int child_index = check_node_exists(current, c);
        if (child_index == -1)
            return out; // there arent any words with that prefix

        current = &current->children[child_index];
    }


    std::string word = prefix;
    std::stack<const TreeNode*> node_stack; // for dfs
    std::stack<int> words_counter_stack;    // stack used to keep prefix words counters
    int words_counter;

    // in case provided prefix is a word
    if (current->eow)
        out.push_back(word);

    // push children nodes to node_stack
    // from back to front so then
    // found answers will be from left side of the tree
    // to the right side
    for (int i = current->children.size() - 1; i >= 0; i--)
    {
        // number of words to get with this prefix
        words_counter = current->children.size();
        words_counter_stack.push(words_counter);

        node_stack.push(&current->children[i]);
    }

    while (!node_stack.empty())
    {
        current = node_stack.top(); node_stack.pop();
        word += current->c;

        // we got to the end of some word
        if (current->eow)
        {
            out.push_back(word);
            LOG_INFO("word found");

            // we got all the words we wanted with current prefix
            if (--words_counter == 0)
            {
                prefix.pop_back();

                if (!words_counter_stack.empty())
                {
                    words_counter = words_counter_stack.top(); words_counter_stack.pop();
                }
            }

            word = prefix; // ready the word variable for next word
        }

        if (current->children.size() > 1)
        {
            words_counter = current->children.size();
            words_counter_stack.push(words_counter);

            // since we will be coming back to this node
            prefix += current->c;
        }

        for (int i = current->children.size() - 1; i >= 0; i--)
            node_stack.push(&current->children[i]);
    }

    return out;
}

size_t Tree::size() const
{
    return m_size;
}

const TreeNode* Tree::root() const
{
    return &m_root;
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
