#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#include <Tree.h>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::microseconds;

std::vector<std::string> find_in_vector(const std::vector<std::string>& vector, const std::string& prefix);

int main()
{
    std::vector<std::string> wordlist;
    std::fstream file("words.txt", std::ios::in);

    int word_counter = 0;
    std::cout << "Putting elements into a vector from file: ";
    auto start = high_resolution_clock::now();
    if (file.is_open())
    {
        std::string word;
        while (getline(file, word))
        {
            wordlist.push_back(word);
            word_counter++;
        }
    } file.close();
    auto stop = high_resolution_clock::now();

    std::cout << duration_cast<milliseconds>(stop - start).count() << "ms\n";
    std::cout << "Elements put into a vector: " << word_counter << "\n";

    std::cout << "Creating Tree object from vector: ";
    start = high_resolution_clock::now();
    st::Tree t(wordlist);
    stop = high_resolution_clock::now();
    std::cout << duration_cast<milliseconds>(stop - start).count() << "ms\n\n";

    std::vector<std::string> prefixes = {"b", "br", "bro"};
    for (const std::string& prefix : prefixes)
    {
        std::cout << "Searching the vector with prefix '" << prefix << "': ";
        start = high_resolution_clock::now();
        std::vector<std::string> found = find_in_vector(wordlist, prefix);
        stop = high_resolution_clock::now();
        std::cout << duration_cast<microseconds>(stop - start).count() << "us; (found words: " << found.size() << ")\n";

        std::cout << "Searching the Tree with prefix '" << prefix << "': ";
        start = high_resolution_clock::now();
        found = t.find(prefix);
        stop = high_resolution_clock::now();
        std::cout << duration_cast<microseconds>(stop - start).count() << "us; (found words: " << found.size() << ")\n\n";
    }

    return 0;
}

std::vector<std::string> find_in_vector(const std::vector<std::string>& vector, const std::string& prefix)
{
    std::vector<std::string> out;

    for (const std::string& word : vector)
        if (word.substr(0, prefix.size()) == prefix)
            out.push_back(word);

    return out;
}
