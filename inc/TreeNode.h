#ifndef SEARCH_TREE_TREENODE_H
#define SEARCH_TREE_TREENODE_H

#include <vector>

// structure of a single tree node
// wondering whether it even should be public
// maybe move it to Tree.cpp?
struct TreeNode
{
    // todo: make it work for utf-8 characters too
    char c;                             // single character
    std::vector<TreeNode> children;     // list of all children nodes
    bool eow = false;                   // end of word flag

    TreeNode() = default;

    // for std::vector.emplace_back()
    TreeNode(char c)
    {
        this->c = c;
    }
};

#endif //SEARCH_TREE_TREENODE_H
