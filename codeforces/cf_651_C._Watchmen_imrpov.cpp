// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/651/problem/C
// TLE @ TEST 10
// This solution takes
// ./cf_651_C._Watchmen < test.txt  2.00s user 0.06s system 99% cpu 2.066 total
// 2.066 s (for test.txt)
#include <map>
#include <set>
#include <stdio.h>
#include <vector>
struct point
{
    int x;
    int y;
    bool operator<(const point &other) const
    {
        if (x == other.x)
        {
            return y < other.y;
        }
        if (y == other.y)
        {
            return x < other.x;
        }
        else
        {
            return x < other.x;
        }
    }
};
int main()
{
    int n, pairs = 0;
    // Have two maps, one for count of point x and occurrences
    // And another for point.y and its occurrences.
    // Say three points are (5, 3), (7, 3), (9, 3), (8, 3) ->
    // points y map [3] = 4
    // And the number of pairs possible are 4 * 3 = 12

    std::map<int, std::vector<point>> xmap;
    std::map<int, std::vector<point>> ymap;
    std::set<std::pair<point, point>> possible_pairs;

    scanf("%d", &n);

    for (int t = 0; t < n; t++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        xmap[x].push_back({x, y});
        ymap[y].push_back({x, y});
    }

    for (const auto &rec : xmap)
    {
        int N = rec.second.size();
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                possible_pairs.insert(
                    std::make_pair(rec.second[i], rec.second[j]));
                pairs++;
            }
        }
    }

    for (const auto &rec : ymap)
    {
        int N = rec.second.size();
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                auto pr1 = std::make_pair(rec.second[i], rec.second[j]);
                auto pr2 = std::make_pair(rec.second[j], rec.second[i]);
                if (possible_pairs.find(pr1) != possible_pairs.end())
                {
                    continue;
                }
                if (possible_pairs.find(pr2) != possible_pairs.end())
                {
                    continue;
                }
                pairs++;
            }
        }
    }

    printf("%d\n", pairs);
    return 0;
}
