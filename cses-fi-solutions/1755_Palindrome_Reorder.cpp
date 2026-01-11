#include <iostream>

// If there are more than one character having odd number of repetition, there is no solution

#define CHR(x) (x - 'A')
int table[26] = {0};

int main()
{
    int idx = 0;
    int odd_index = -1;
    std::string line;
    std::cin >> line;
    for (const auto &ch : line)
        table[CHR(ch)]++;
    // Check for no solution condition
    for (const auto &entry : table)
    {
        if (entry % 2 != 0)
        {
            if (odd_index >= 0)
            {
                std::cout << "NO SOLUTION" << std::endl;
                return 0;
            }
            odd_index = idx;
        }
        idx++;
    }
    // Print the first half of the elements
    for (int i = 0; i < 26; i++)
    {
        std::cout << std::string(table[i] / 2, 'A' + i);
    }
    if (odd_index >= 0)
        std::cout << (char)(odd_index + 'A');
    for (int i = 25; i >= 0; i--)
    {
        std::cout << std::string(table[i] / 2, 'A' + i);
    }
    std::cout << std::endl;
}