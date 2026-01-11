#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <sstream>
#include <vector>

using grid = std::vector<std::string>;

bool is_surrounding_char_gear(const grid &g, int i, int j, int *row, int *col)
{
    // Check all 8 chars surrounding this character
    for (int l = -1; l <= 1; l++)
    {
        for (int m = -1; m <= 1; m++)
        {
            if ((i + l) < 0 || (j + m) < 0 || (i + l) >= g.size() || (j + m) >= g[0].size())
                continue;
            auto ch = g[i + l][j + m];
            if (ch == '*')
            {
                *row = i + l;
                *col = j + m;
                return true;
            }
        }
    }
    return false;
}

void get_numbers_touching_symbols(const grid &g, int row,
                                  std::map<std::pair<int, int>, std::vector<int>> &gear_numbers)

{
    std::string current_number;
    bool is_touching_symbol = false;
    int gear_row, gear_col;

    std::vector<std::pair<int, int>> gears;

    for (int i = 0; i < g[row].size(); i++)
    {
        if (isdigit(g[row][i]) && is_surrounding_char_gear(g, row, i, &gear_row, &gear_col))
        {
            is_touching_symbol = true;
            auto t = std::make_pair(gear_row, gear_col);
            bool flag = true;
            for (const auto &p : gears)
            {
                if (p == t)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                gears.push_back(t);
            }
        }
        if (!isdigit(g[row][i]))
        {
            if (current_number.size() && is_touching_symbol)
            {
                for (const auto &gear : gears)
                {
                    gear_numbers[gear].push_back(std::stoi(current_number));
                }
                gears.clear();
                is_touching_symbol = false;
            }
            current_number.clear();
            continue;
        }
        current_number.push_back(g[row][i]);
    }
    if (current_number.size() && is_touching_symbol)
    {
        for (const auto &gear : gears)
        {
            gear_numbers[gear].push_back(std::stoi(current_number));
        }
    }
    current_number.clear();
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
    std::map<std::pair<int, int>, std::vector<int>> gear_numbers;
    int answer = 0;
    for (int i = 0; i < g.size(); i++)
    {
        get_numbers_touching_symbols(g, i, gear_numbers);
    }
    for (const auto &rec : gear_numbers)
    {
        std::cout << rec.first.first << ", " << rec.first.second << ": ";
        std::copy(rec.second.begin(), rec.second.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    for (const auto &rec : gear_numbers)
    {
        if (rec.second.size() == 2)
        {
            answer += rec.second[0] * rec.second[1];
        }
    }
    std::cout << "Answer: " << answer << std::endl;
}