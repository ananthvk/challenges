// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/59/problem/A
#include <ctype.h>
#include <iostream>
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::string str;
    int u = 0, l = 0;
    std::cin >> str;
    for (auto &ch : str)
    {
        if (std::isupper(ch))
        {
            u++;
        }
        if (std::islower(ch))
        {
            l++;
        }
    }
    if (u > l)
    {
        for (auto &ch : str)
        {
            ch = toupper(ch);
        }
    }
    else
    {
        for (auto &ch : str)
        {
            ch = tolower(ch);
        }
    }
    std::cout << str << "\n";
    return 0;
}
