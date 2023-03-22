#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_map>
#include "PrefTree.h"

void umap(const std::string& text, std::string word)
{
    using namespace std;
    unordered_map<std::string, size_t> dict;
    string str = "";
    for (const auto& ch : text) // кроме последнего слова
    {
        if (isalpha(ch) || ch == '\'')
            str += ch;
        else if (str.size() > 0)
        {
            ++dict[str];
            str = "";
        }
    }
    cout << "\ndict size: " << dict.size() << endl;
    cout << word << ": " << dict[word] << endl;
}

int main()
{
    std::string word = "wiki";
    std::string text;
    std::ifstream fin("data.txt", std::ios::binary);
    if (!fin.is_open())
    {
        std::cout << "not open!" << std::endl;
        return 0;
    }
    text.append((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
 
    auto time_one = std::chrono::steady_clock::now();
    umap(text, word);
    auto time_two = std::chrono::steady_clock::now();
    std::cout << "umap\t" << std::chrono::duration_cast<std::chrono::microseconds>(time_two - time_one).count() / 1e6 << " sec\n" << std::endl;

    time_one = std::chrono::steady_clock::now();
    PrefTree* pt = new PrefTree();
    pt->insert(text);
    time_two = std::chrono::steady_clock::now();
    std::cout << "PrefTree size: " << pt->get_size() << std::endl << word << ": " << pt->get_count(word) << std::endl;
    std::cout << "PrefTree\t" << std::chrono::duration_cast<std::chrono::microseconds>(time_two - time_one).count() / 1e6 << " sec\n" << std::endl;
}