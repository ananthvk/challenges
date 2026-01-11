// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/1809/problem/A
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

#define POS_0 8
#define POS_1 4
#define POS_2 2
#define POS_3 1

std::ostream &operator<<(std::ostream &os, const std::vector<int> v)
{
    for (const auto &c : v)
    {
        os << c << " ";
    }
    return os;
}
std::ostream &operator<<(std::ostream &os, const std::vector<char> v)
{
    for (const auto &c : v)
    {
        os << c << " ";
    }
    return os;
}

typedef std::tuple<std::string, int, char, int> record;

int get_mask(int i)
{
    if (i == 0)
    {
        return POS_0;
    }
    if (i == 1)
    {
        return POS_1;
    }
    if (i == 2)
    {
        return POS_2;
    }
    if (i == 3)
    {
        return POS_3;
    }
    else
    {
        throw std::logic_error("*I > 3");
    }
}

int get_value(int i, int state)
{
    if (i == 0)
    {
        return ((state & POS_0) >> 3);
    }
    if (i == 1)
    {
        return (state & POS_1) >> 2;
    }
    if (i == 2)
    {
        return (state & POS_2) >> 1;
    }
    if (i == 3)
    {
        return state & POS_3;
    }
    else
    {
        throw std::logic_error("I > 3");
    }
}

void solution(std::string light, int state, int depth, char prev,
              std::vector<int> &solutions, std::set<record> &rec)
{
    // Base cases
    // ===========
    // 1. This state has already been examined
    // 2. Solution is found
    if (state == 15)
    {
        solutions.push_back(depth);
    }
    auto hit = std::make_tuple(light, state, prev, depth);
    if (rec.find(hit) != rec.end())
    {
        // return;
    }
    std::cout << "|";
    for (int i = 0; i < depth; i++)
    {
        std::cout << "-";
    }
    std::cout << " " << ((state & 8) >> 3) << " " << ((state & 4) >> 2) << " "
              << ((state & 2) >> 1) << " " << (state & 1) << "\n";
    rec.insert(std::make_tuple(light, state, prev, depth));
    for (int i = 0; i < light.size(); i++)
    {
        if (light[i] != prev)
        {
            solution(light, state ^ get_mask(i), depth + 1, light[i], solutions,
                     rec);
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // To take n number of test cases from input
    int num_tests;
    std::cin >> num_tests;
    std::string lights;
    for (int tno = 0; tno < num_tests; tno++)
    {
        std::cin >> lights;
        int state = 0;
        std::set<record> rec;
        std::vector<int> solns;
        solution(lights, state, 0, 'A', solns, rec);
        if (solns.empty())
        {
            std::cout << "-1\n";
        }
        else
        {
            std::sort(solns.begin(), solns.end());
            std::cout << solns[0] << "\n";
        }
    }
    return 0;
}