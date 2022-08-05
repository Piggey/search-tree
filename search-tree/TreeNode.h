#pragma once

#include <vector>

namespace st
{

// structure of a single tree node
struct TreeNode
{
    // todo: make it work for utf-8 characters too
    char c = -1;                        // single character
    TreeNode* parent = nullptr;         // pointer to the parent node
    std::vector<TreeNode*> children;    // list of all children nodes
    bool eow = false;                   // end of word flag

    TreeNode() = default;

    explicit TreeNode(char c) : c(c) {}

    TreeNode(char c, TreeNode* parent) : c(c), parent(parent) {}
};
}