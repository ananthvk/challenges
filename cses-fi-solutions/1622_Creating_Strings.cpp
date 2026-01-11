#include <algorithm>
#include <iostream>
#include <set>

void solution(std::string current_str, const std::string &remaining_characters,
              std::set<std::string> &s)
{
    if (remaining_characters.empty())
    {
        s.insert(current_str);
    }
    for (size_t i = 0; i < remaining_characters.size(); i++)
    {
        auto t = remaining_characters;
        t.erase(i, 1);
        solution(current_str + remaining_characters[i], t, s);
    }
}

int main()
{
    std::string line, current;
    std::cin >> line;
    // Sort the string in non decreasing order before proceeding
    std::sort(line.begin(), line.end());
    std::set<std::string> solutions;
    // solution(current, line, solutions);
    
    // Alternate solution using STL
    solutions.insert(line);
    while (std::next_permutation(line.begin(), line.end()))
    {
        solutions.insert(line);
    }
    std::cout << solutions.size() << std::endl;
    for (const auto &soln : solutions)
    {
        std::cout << soln << std::endl;
    }
}
