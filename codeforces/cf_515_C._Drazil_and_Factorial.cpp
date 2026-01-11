// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/515/problem/C
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void modify(int i, std::map<int, int> &m, char op)
{
    if (op == '-')
    {
        switch (i)
        {
        case 0:
            break;
        case 1:
            break;
        case 4:
            m[2] -= 2;
            break;
        case 6:
            m[2]--;
            m[3]--;
            break;
        case 8:
            m[2] -= 3;
            break;
        case 9:
            m[3] -= 2;
            break;
        default:
            m[i] -= 1;
            break;
        }
    }
    else
    {
        switch (i)
        {
        case 0:
            break;
        case 1:
            break;
        case 4:
            m[2] += 2;
            break;
        case 6:
            m[2]++;
            m[3]++;
            break;
        case 8:
            m[2] += 3;
            break;
        case 9:
            m[3] += 2;
            break;
        default:
            m[i] += 1;
            break;
        }
    }
}

void add_factorial_numbers(int n, std::map<int, int> &m)
{
    for (int i = n; i > 1; i--)
    {
        modify(i, m, '+');
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    int n;
    std::string number;

    std::cin >> n >> number;

    std::map<int, int> digit_counts_map;

    for (const auto &ch : number)
    {
        add_factorial_numbers(ch - '0', digit_counts_map);
    }

    for (auto iter = digit_counts_map.rbegin(); iter != digit_counts_map.rend();
         iter++)
    {
        for (int i = 0; i < iter->second; i++)
        {
            for (int j = iter->first - 1; j > 1; j--)
            {
                modify(j, digit_counts_map, '-');
            }
        }
    }

    std::vector<int> result;

    for (const auto &pair : digit_counts_map)
    {
        for (int i = 0; i < pair.second; i++)
        {
            result.push_back(pair.first);
        }
    }

    std::sort(result.begin(), result.end(), std::greater<>());
    for (const auto &x : result)
    {
        std::cout << x;
    }
    std::cout << "\n";
    return 0;
}
