// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/371/problem/B
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

void solution(int a, int b, int depth, int &minsoln)
{

    if (a == b)
    {
        if (depth < minsoln)
        {
            minsoln = depth;
        }
        return;
    }

    if (a < 1)
    {
        return;
    }

    if (a % 2 == 0)
    {
        solution(b, a / 2, depth + 1, minsoln);
        solution(a / 2, b, depth + 1, minsoln);
    }

    if (a % 3 == 0)
    {
        solution(b, a / 3, depth + 1, minsoln);
        solution(a / 3, b, depth + 1, minsoln);
    }

    if (a % 5 == 0)
    {
        solution(b, a / 5, depth + 1, minsoln);
        solution(a / 5, b, depth + 1, minsoln);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int a, b;
    int minsoln = std::numeric_limits<int>::max();
    std::cin >> a >> b;
    solution(std::max(a, b), std::min(a, b), 0, minsoln);
    if (minsoln == std::numeric_limits<int>::max())
    {
        std::cout << "-1\n";
    }
    else
    {
        std::cout << minsoln << "\n";
    }
    return 0;
}
