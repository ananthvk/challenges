#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
#include <algorithm>

// On trying out various solutions to the problem, it can be seen that
// the gray code is the refelction of the values in a standard truth table
// For example, for n = 3
// 0 0 0
// 0 0 1
// 0 1 1
// 0 1 0
// -----
// 1 1 0
// 1 1 1
// 1 0 1
// 1 0 0
// Notice that the two right bits are reflected
// For n = 4, we write 8 0s and 8 1s then write the reflection of the above table for the ones part

std::vector<std::string> solution(int n)
{
    assert(n >= 1);
    if (n == 1)
    {
        return {"0", "1"};
    }
    auto s = solution(n - 1);
    // Set 2^(n-1) bits to 0, merge with s
    // Then set the remaining 2^(n-1) bits to 1, merge with the reverse of s
    std::vector<std::string> tmp = s;
    std::for_each(tmp.begin(), tmp.end(), [](std::string &s)
                  { s = "0" + s; });
    std::transform(s.rbegin(), s.rend(), std::back_inserter(tmp), [](std::string s)
                   { return "1" + s; });
    return tmp;
}

int main()
{
    int n;
    std::cin >> n;
    auto s = solution(n);
    for (const auto &line : s)
    {
        std::cout << line << std::endl;
    }
}