#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>

size_t naive(const std::string& str, const std::string& sub)
{
    size_t n = str.size();
    size_t m = sub.size();
    size_t j = 0;
    for (int i = 0; i < n - m + 1; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (str[i + j] != sub[j])
                break;
        }
        if (j == m)
            return i;
    }
    return std::string::npos;
}

size_t kmp(const std::string& str, const std::string& sub)
{
    int m = str.length();
    int n = sub.length();

    if (n == 0)
    {
        return std::string::npos;
    }

    if (m < n)
    {
        return std::string::npos;
    }

    int* next = new int[n + 1] {0};
    int j;
    for (int i = 1; i < n; i++)
    {
        j = next[i];
        while (j > 0 && sub[j] != sub[i]) {
            j = next[j];
        }

        if (j > 0 || sub[j] == sub[i]) {
            next[i + 1] = j + 1;
        }
    }
    
    j = 0;
    for (int i = 0; i < m; i++)
    {
        if (str[i] == sub[j])
        {
            if (++j == n) {
                delete[] next;
                return i - j + 1;
            }
        }
        else if (j > 0)
        {
            j = next[j];
            i--;    
        }
    }
}

void badCharHeuristic(std::string str, int size, int badchar[256])
{
    int i;
    for (i = 0; i < 256; i++)
        badchar[i] = -1;
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

size_t search(std::string txt, std::string pat)
{
    int m = pat.size();
    int n = txt.size();
    int badchar[256];  
    badCharHeuristic(pat, m, badchar);
    int s = 0; 
               
    while (s <= (n - m))
    {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j])
            j--;
        if (j < 0)
        {
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
            return s;
        }
        else
            s += std::max(1, j - badchar[txt[s + j]]);
    }
}


int main()
{
    std::string str, sub = "He won it four times with Montreal";
    std::ifstream fin("engwiki_ascii.txt", std::ios::binary);

    if (!fin.is_open())
    {
        std::cout << "not open!" << std::endl;
        return 0;
    }
    str.append((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

    size_t n = 10;
    std::vector<size_t> timesVect(n);
    std::vector<size_t> idx(n);

    std::cout << "kmp" << std::endl;
    for (size_t i = 0; i < n; i++)
    {
        auto firstT = std::chrono::high_resolution_clock::now();
        auto index = kmp(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            idx[i] = index;
        auto secondT = std::chrono::high_resolution_clock::now();
        timesVect[i] = std::chrono::duration_cast<std::chrono::milliseconds>(secondT - firstT).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        std::cout << idx[i] << '\t' << timesVect[i] << std::endl;
    }

    std::cout << std::endl << "bm" << std::endl;
    for (size_t i = 0; i < n; i++)
    {
        auto firstT = std::chrono::high_resolution_clock::now();
        auto index = search(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            idx[i] = index;
        auto secondT = std::chrono::high_resolution_clock::now();
        timesVect[i] = std::chrono::duration_cast<std::chrono::milliseconds>(secondT - firstT).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        std::cout << idx[i] << '\t' << timesVect[i] << std::endl;
    }

    std::cout << std::endl << "naive" << std::endl;
    for (size_t i = 0; i < n; i++)
    {
        auto firstT = std::chrono::high_resolution_clock::now();
        auto index = naive(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            idx[i] = index;
        auto secondT = std::chrono::high_resolution_clock::now();
        timesVect[i] = std::chrono::duration_cast<std::chrono::milliseconds>(secondT - firstT).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        std::cout << idx[i] << '\t' << timesVect[i] << std::endl;
    }
    
    
    std::cout << std::endl << "std::find" << std::endl;
    for (size_t i = 0; i < n; i++)
    { 
        auto firstT = std::chrono::high_resolution_clock::now();
        auto index = str.find(sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            idx[i] = index;
        auto secondT = std::chrono::high_resolution_clock::now();
        timesVect[i] = std::chrono::duration_cast<std::chrono::milliseconds>(secondT - firstT).count();
    }
    for (size_t i = 0; i < n; i++)
    {
        std::cout << idx[i] << '\t' << timesVect[i] << std::endl;
    }
}