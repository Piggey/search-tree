#include "search-tree/Tree.h"
#include "tinylogger/tinylogger.h"

#include <stack>

/**
 * @brief finds the index of a child node with matching character value
 * @param parent: parent TreeNode pointer to be checked
 * @param c: character to be checked
 * @attention this function returns -1 when child node was NOT found
 * @return index of the child node in the parent's array of children.
 * returns -1 if node was not found.
 */
inline int get_child_index(const st::TreeNode* parent, char c);

st::Tree::Tree()
{
    m_root.c = 0;
    m_size = 0;
    tlog::info() << "new tree object created";
}

st::Tree::Tree(const std::vector<std::string>& wordlist)
{
    tlog::info() << "creating new tree object with wordlist of size " << wordlist.size();
    m_root.c = 0;
    m_size = 0;

    for (const std::string& word: wordlist)
        if (!word.empty())
            put(word);
}

void st::Tree::put(const std::string& word)
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
        int child_index = get_child_index(current, c);

        if (child_index == -1) // does not exist
        {
            // create and add a new node
            auto* child = new TreeNode(c);
            current->children.push_back(child);
            node_created = true;

            current = child;
        }
        else // node already exists
        {
            current = current->children[child_index];
        }
    }

    if (!node_created && current->eow)
    {
        tlog::warning() << "word already exists in tree: " << word;
        return; // user put 2 same words
    }

    m_size++;
    current->eow = true;
    tlog::info() << word << " inserted successfully into a tree";
}

void st::Tree::remove(const std::string& word)
{
    if (m_size == 0)
    {
        tlog::warning() << "tried to remove a word from an empty tree";
        return;
    }

    TreeNode* current = &m_root;

    // keep the parent node and child index of the node we want to delete
    // stack since we want to delete them bottom up
    std::stack<std::pair<TreeNode*, int>> to_be_deleted;

    // collect the nodes that will be deleted
    for (unsigned int i = 0; i < word.size(); i++)
    {
        char c = word[i];
        int child_index = get_child_index(current, c);

        // word doesn't exist in a Tree
        if (child_index == -1)
        {
            tlog::warning() << "tried to remove a word that does not exist. word: " << word;
            return;
        }

        // one word is using current node
        if (find(word.substr(0, i + 1)).size() <= 1)
        {
            to_be_deleted.push(std::make_pair(current, child_index));
        }

        current = current->children[child_index];
    }

    current->eow = false;   // unset the end of word flag on the last node (if was used)
    m_size--;               // decrement words counter

    // delete the nodes
    while (!to_be_deleted.empty())
    {
        auto pair = to_be_deleted.top(); to_be_deleted.pop();
        auto pos = pair.first->children.begin() + pair.second;

        tlog::info() << "removing node '"
                << pair.first->children[pair.second]->c
                << "' (child of '" << pair.first->c << "')";

        TreeNode* tmp = pair.first->children[pair.second];
        pair.first->children.erase(pos); // unhook the connection between nodes
        delete tmp; // free the memory
    }
}

std::vector<std::string> st::Tree::find(std::string prefix) const
{
    std::vector<std::string> out; // list of found words
    const TreeNode* current = &m_root;

    tlog::info() << "starting searching for prefix: " << prefix;

    // empty Tree case
    if (m_size == 0)
    {
        tlog::warning() << "tried to search an empty tree";
        return out;
    }

    // go through the nodes from the prefix, if they exist
    for (char c : prefix)
    {
        int child_index = get_child_index(current, c);
        if (child_index == -1)
            return out; // there aren't any words with that prefix

        current = current->children[child_index];
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
    // todo: just use a fucking queue
    for (int i = current->children.size() - 1; i >= 0; i--)
    {
        // number of words to get with this prefix
        words_counter = current->children.size();
        words_counter_stack.push(words_counter);

        node_stack.push(current->children[i]);
    }

    while (!node_stack.empty())
    {
        current = node_stack.top(); node_stack.pop();
        word += current->c;

        // we got to the end of some word
        if (current->eow)
        {
            out.push_back(word);

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
            node_stack.push(current->children[i]);
    }

    tlog::info() << "found " << out.size() << " words with provided prefix";
    return out;
}

size_t st::Tree::size() const
{
    return m_size;
}

const st::TreeNode* st::Tree::root() const
{
    return &m_root;
}

st::Tree::~Tree()
{

}

inline int get_child_index(const st::TreeNode* parent, char c)
{
    for (unsigned int i = 0; i < parent->children.size(); i++)
        if (parent->children[i]->c == c)
            return (int) i;

    return -1;
}
