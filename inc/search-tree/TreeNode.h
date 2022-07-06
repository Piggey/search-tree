#pragma once

#include <vector>

namespace st
{

// structure of a single tree node
struct TreeNode
{
    // todo: make it work for utf-8 characters too
    char c = -1;                            // single character
    std::vector<TreeNode*> children;  // list of all children nodes
    bool eow = false;                       // end of word flag

    TreeNode() = default;

    // for std::vector.emplace_back()
    explicit TreeNode(char c)
    {
        this->c = c;
    }
};
}