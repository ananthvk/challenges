// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/651/problem/C
// TLE @ TEST 10
// This solution takes
// ./cf_651_C._Watchmen < test.txt  97.11s user 0.01s system 99% cpu 1:37.23
// total 1:37 minutes to solve

#include <stdio.h>
#include <vector>

struct point
{
    int x;
    int y;
};

int main()
{
    int n, pairs = 0;
    scanf("%d", &n);
    std::vector<point> positions;
    positions.reserve(n);
    for (int t = 0; t < n; t++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        positions.push_back({x, y});
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            auto p1 = positions[i];
            auto p2 = positions[j];
            if ((p1.x - p2.x) == 0 || (p1.y - p2.y) == 0)
            {
                pairs++;
            }
        }
    }
    printf("%d\n", pairs);
    return 0;
}
