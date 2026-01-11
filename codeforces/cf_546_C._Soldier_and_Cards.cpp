// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/546/problem/C
#include <deque>
#include <iostream>
#include <map>
#include <vector>

std::ostream &operator<<(std::ostream &os, const std::deque<int> &dq)
{
    for (auto &i : dq)
    {
        os << i << " ";
    }
    os << "\n";
    return os;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, k1, k2, tmp, p1, p2, moves = 0;
    std::deque<int> dp1;
    std::deque<int> dp2;
    std::map<std::deque<int>, std::deque<int>> visited;
    std::cin >> n;
    std::cin >> k1;
    for (int i = 0; i < k1; i++)
    {
        std::cin >> tmp;
        dp1.push_front(tmp);
    }
    std::cin >> k2;
    for (int i = 0; i < k2; i++)
    {
        std::cin >> tmp;
        dp2.push_front(tmp);
    }
    while (!(dp1.empty() || dp2.empty()))
    {
        /*
        std::cout << "Start of move " << moves << "\n";
        std::cout << "dp1: " << dp1;
        std::cout << "dp2: " << dp2;
        std::cout << "========\n";
        */
        visited[dp1] = dp2;

        p1 = dp1.back();
        dp1.pop_back();

        p2 = dp2.back();
        dp2.pop_back();

        if (p1 > p2)
        {
            dp1.push_front(p2);
            dp1.push_front(p1);
        }
        else
        {
            dp2.push_front(p1);
            dp2.push_front(p2);
        }
        // Handle cycles

        if (visited.find(dp1) != visited.end())
        {
            if (visited.find(dp1)->second == dp2)
            {
                std::cout << "-1\n";
                return 0;
            }
        }
        moves++;
    }
    if (dp1.empty())
    {
        std::cout << moves << " " << 2 << "\n";
    }
    else
    {
        std::cout << moves << " " << 1 << "\n";
    }
    return 0;
}
