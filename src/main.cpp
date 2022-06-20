#include <iostream>
#include <vector>
#include <fstream>

#include "Tree.h"

std::vector<std::string> parse_file(const char* wordlist_filepath);

int main(int argc, char** argv)
{
    // not enough or too many arguments provided
    if (argc <= 1 || argc > 2)
    {
        std::cout << "usage: search-tree <path-to-wordlist>" << "\n";
        return 1;
    }

    // parse the wordlist file
    std::vector<std::string> wordlist = parse_file(argv[1]);

    // create a tree
    Tree t(wordlist);
    std::cout << "size: " << t.size() << "\n";
    return 0;
}

std::vector<std::string> parse_file(const char* wordlist_filepath)
{
    std::vector<std::string> out;
    std::ifstream file(wordlist_filepath);

    while (file) {
        std::string word;
        file >> word;
        out.push_back(word);
    } file.close();

    return out;
}
