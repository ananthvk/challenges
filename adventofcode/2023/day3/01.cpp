#include <fstream>
#include <iostream>
#include<algorithm>
#include <iterator>
#include <sstream>
#include<numeric>
#include <vector>

using grid = std::vector<std::string>;

bool is_surrounding_char_symbol(const grid &g, int i, int j)
{
    // Check all 8 chars surrounding this character
    for (int l = -1; l <= 1; l++)
    {
        for (int m = -1; m <= 1; m++)
        {
            if((i+l) < 0 || (j + m) < 0 || (i + l) >= g.size() || (j + m) >= g[0].size())
                continue;
            auto ch = g[i + l][j + m];
            if (!isdigit(ch) && ch != '.')
                return true;
        }
    }
    return false;
}

int get_numbers_touching_symbols(const grid &g, int row)
{
    std::string current_number;
    std::vector<int> numbers;
    bool is_touching_symbol = false;
    for (int i = 0; i < g[row].size(); i++)
    {
        // check if the digit is touching a symbol
        if (isdigit(g[row][i]) && !is_touching_symbol && is_surrounding_char_symbol(g, row, i))
        {
            is_touching_symbol = true;
        }
        if (!isdigit(g[row][i]))
        {
            if (current_number.size() && is_touching_symbol)
            {
                numbers.push_back(std::stoi(current_number));
                is_touching_symbol = false;
            }
            current_number.clear();
            continue;
        }
        current_number.push_back(g[row][i]);
    }
    if (current_number.size() && is_touching_symbol)
    {
        numbers.push_back(std::stoi(current_number));
    }
    current_number.clear();
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}

int main()
{
    std::ifstream ifs("input.txt");
    std::string line;
    grid g;
    while (std::getline(ifs, line))
    {
        g.push_back(line);
    }
    int answer = 0;
    for (int i = 0; i < g.size(); i++)
    {
        answer += get_numbers_touching_symbols(g, i);
    }
    std::cout<<"Answer: "<<answer<<std::endl;
}