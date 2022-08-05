#include "Tree.h"
#include "TreeNode.h"

#include <stack>
#include <queue>
#include <stdexcept>
#include <algorithm>

/**
 * @brief finds the index of a child node with matching character value
 * @param parent: parent TreeNode pointer to be checked
 * @param c: character to be checked
 * @attention this function returns -1 when child node was NOT found
 * @return index of the child node in the parent's array of children.
 * returns -1 if node was not found.
 */
inline int get_child_index(const st::TreeNode* parent, char c);

/**
 * @brief gets all the possible paths with given prefix. There's only one path when ignore_case_sens is set to false.
 * @param root: pointer to the root node of the Tree object to be searched through.
 * @param prefix: word prefix
 * @param ignore_case_sens: option to be case-insensitive.
 * @return a queue of TreeNode object pointers at the end of the prefixes
 */
std::queue<const st::TreeNode*> get_all_possible_paths(const st::TreeNode* root, const std::string& prefix, bool ignore_case_sens);

/**
 * @brief traverses through the Tree to get back the word
 * @param final_node: pointer to the TreeNode that's the final node of some word (eow set to true)
 * @return a std::string word of final node
 */
inline std::string get_word(const st::TreeNode* final_node);

st::Tree::Tree()
{
    m_root = new TreeNode(0);
    m_size = 0;
}

st::Tree::Tree(const std::vector<std::string>& wordlist)
{
    m_root = new TreeNode(0);
    m_size = 0;

    for (const std::string& word: wordlist)
        if (!word.empty())
            put(word);
}

void st::Tree::put(const std::string& word)
{
    // store the node we're putting a new node into
    // starting from root
    TreeNode* current = m_root;

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
            auto* child = new TreeNode(c, current);
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
        return; // user put 2 same words

    m_size++;
    current->eow = true;
}

void st::Tree::remove(const std::string& word)
{
    if (m_size == 0)
        return;

    TreeNode* current = m_root;

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
            return;

        // one word is using current node
        if (find(word.substr(0, i + 1)).size() <= 1)
            to_be_deleted.emplace(current, child_index);

        current = current->children[child_index];
    }

    current->eow = false;   // unset the end of word flag on the last node (if was used)
    m_size--;               // decrement words counter

    // delete the nodes
    while (!to_be_deleted.empty())
    {
        auto pair = to_be_deleted.top(); to_be_deleted.pop();
        auto pos = pair.first->children.begin() + pair.second;

        TreeNode* tmp = pair.first->children[pair.second];
        pair.first->children.erase(pos); // unhook the connection between nodes
        delete tmp; // free the memory
    }
}

std::vector<std::string> st::Tree::find(const std::string& prefix, bool ignore_case_sens) const
{
    std::vector<std::string> out; // list of found words to be returned

    // empty Tree case
    if (m_size == 0)
        return out;

    // get all paths with their prefixes
    auto paths = get_all_possible_paths(m_root, prefix, ignore_case_sens);
    while (!paths.empty())
    {
        const TreeNode* current = paths.front(); paths.pop();

        std::stack<const TreeNode*> node_stack; // for dfs
        node_stack.push(current);
        while(!node_stack.empty())
        {
            current = node_stack.top(); node_stack.pop();

            // we got to the end of some word
            if (current->eow)
                out.emplace_back(get_word(current));

            // add all the children nodes to the stack
            for (unsigned int i = current->children.size(); i-- > 0; )
                node_stack.push(current->children[i]);
        }
    }

    return out;
}

size_t st::Tree::size() const
{
    return m_size;
}

st::Tree::~Tree()
{
    std::stack<TreeNode*> to_be_deleted;
    std::queue<TreeNode*> q;

    q.push(m_root);

    // add all the allocated nodes on the stack
    while (!q.empty())
    {
        TreeNode* node = q.front(); q.pop();
        to_be_deleted.push(node);

        for (TreeNode* child : node->children)
            q.push(child);
    }

    // actually freeing the memory
    while (!to_be_deleted.empty())
    {
        TreeNode* node = to_be_deleted.top(); to_be_deleted.pop();
        delete node;
    }
}

inline int get_child_index(const st::TreeNode* parent, char c)
{
    for (unsigned long i = 0; i < parent->children.size(); i++)
        if (parent->children[i]->c == c)
            return (int) i;

    return -1;
}

// structure used to keeping the data necessary for searching case-insensitive prefixes
struct TreeFrame
{
    const st::TreeNode* node;
    int level;                  // level of how deep into the Tree this TreeNode is

    TreeFrame(const st::TreeNode *node, int level)
        : node(node), level(level) {}
};

std::queue<const st::TreeNode*> get_all_possible_paths(const st::TreeNode* root, const std::string& prefix, bool ignore_case_sens)
{
    // this queue holds only the last TreeNode pointer, along with the used prefix to get there
    std::queue<const st::TreeNode*> out;
    const st::TreeNode* current = root;

    // in case prefix is empty
    if (prefix.empty())
    {
        out.emplace(current);
        return out;
    }

    // old way of doing it
    if (!ignore_case_sens)
    {
        // go through the nodes from the prefix, if they exist
        for (char c : prefix)
        {
            int child_index = get_child_index(current, c);
            if (child_index == -1)
                return out; // there aren't any words with that prefix

            current = current->children[child_index];
        }

        out.emplace(current);
    }
    else
    {
        // temporary stack in pair with the level of how deep the TreeNode is in the Tree
        std::stack<TreeFrame> stack;

        stack.emplace(current, -1);

        while (!stack.empty())
        {
            TreeFrame frame = stack.top(); stack.pop();
            current = frame.node;
            int level = frame.level;

            // we reached the end of the prefix
            if ((unsigned long) level == prefix.size() - 1)
            {
                out.emplace(current);
                continue;
            }

            int index;
            char c = prefix[level + 1];
            // c is lowercase
            if (c >= 'a' && c<= 'z')
            {
                index = get_child_index(current, (char) (c - 32));
                if (index != -1)
                    stack.emplace(current->children[index], level + 1);

                index = get_child_index(current, c);
                if (index != -1)
                    stack.emplace(current->children[index], level + 1);
            }

            // c is uppercase
            else if (c >= 'A' && c <= 'Z')
            {
                index = get_child_index(current, (char) (c + 32));
                if (index != -1)
                    stack.emplace(current->children[index], level + 1);

                index = get_child_index(current, c);
                if (index != -1)
                    stack.emplace(current->children[index], level + 1);
            }

            // c is not a letter
            else
            {
                index = get_child_index(current, c);
                if (index != -1)
                    stack.emplace(current->children[index], level + 1);
            }
        }
    }

    return out;
}

inline std::string get_word(const st::TreeNode* final_node)
{
    const st::TreeNode* tmp = final_node;
    std::string out_word;

    // hopefully this might speed things up
    try { out_word.reserve(30); } catch (std::length_error& e) { fprintf(stderr, "%s", e.what()); }

    while (tmp->parent != nullptr)
    {
        out_word += tmp->c;
        tmp = tmp->parent;
    }

    std::reverse(out_word.begin(), out_word.end());
    return out_word;
}
