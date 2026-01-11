// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/371/problem/B
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <vector>
#define INTEGER_MAX std::numeric_limits<int>::max()
typedef std::pair<int, int> pair;

void solution(int a, int b, int depth, int &minsoln, int &localmin,
              std::map<pair, int> &mem)
{
    auto ab = std::make_pair(a, b);
    if (mem.find(ab) != mem.end())
    {
        int soln = mem[ab];
        if (soln < minsoln)
        {
            minsoln = soln;
        }
        if (soln < localmin)
        {
            localmin = soln;
        }
        return;
    }
    int localmin_ = INTEGER_MAX;
    if (a == b)
    {
        if (depth < minsoln)
        {
            minsoln = depth;
        }
        if (localmin_ < localmin)
        {
            localmin = localmin_;
        }
        return;
    }

    if (a < 1)
    {
        return;
    }

    if (a % 2 == 0)
    {
        solution(b, a / 2, depth + 1, minsoln, localmin_, mem);
        solution(a / 2, b, depth + 1, minsoln, localmin_, mem);
    }

    if (a % 3 == 0)
    {
        solution(b, a / 3, depth + 1, minsoln, localmin_, mem);
        solution(a / 3, b, depth + 1, minsoln, localmin_, mem);
    }

    if (a % 5 == 0)
    {
        solution(b, a / 5, depth + 1, minsoln, localmin_, mem);
        solution(a / 5, b, depth + 1, minsoln, localmin_, mem);
    }
    // If local min is not integer max, this branch has found a solution
    if (localmin != INTEGER_MAX)
    {
        mem[ab] = localmin_;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int a, b;
    int minsoln = INTEGER_MAX;
    int loc;
    std::map<pair, int> mem;
    std::cin >> a >> b;
    solution(std::max(a, b), std::min(a, b), 0, minsoln, loc, mem);
    if (minsoln == INTEGER_MAX)
    {
        std::cout << "-1\n";
    }
    else
    {
        std::cout << minsoln << "\n";
    }
    return 0;
}
