#ifndef SEARCH_TREE_TREENODE_H
#define SEARCH_TREE_TREENODE_H

#include <vector>

// structure of a single tree node
struct TreeNode
{
    // todo: make it work for utf-8 characters too
    char c;                             // single character
    std::vector<TreeNode*> children;    // list of pointers to all children nodes
};

#endif //SEARCH_TREE_TREENODE_H
