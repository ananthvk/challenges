// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/651/problem/C
// TLE @ TEST 10
#include <map>
#include <set>
#include <stdio.h>
#include <vector>
int main()
{
    int n;
    long long int pairs = 0;
    // Have two maps, one for count of polong long int x and occurrences
    // And another for polong long int.y and its occurrences.
    // Say three polong long ints are (5, 3), (7, 3), (9, 3), (8, 3) ->
    // polong long ints y map [3] = 4
    // And the number of pairs possible are 4 * 3 = 12

    std::map<long long int, long long int> xmap;
    std::map<long long int, long long int> ymap;
    std::map<std::pair<long long int, int>, long long int> globalcounts;

    scanf("%d", &n);

    for (long long int t = 0; t < n; t++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        xmap[x]++;
        ymap[y]++;
        globalcounts[std::make_pair(x, y)]++;
    }

    for (const auto &rec : xmap)
    {
        pairs += rec.second * (rec.second - 1) / 2;
    }

    for (const auto &rec : ymap)
    {
        pairs += rec.second * (rec.second - 1) / 2;
    }

    for (const auto &rec : globalcounts)
    {
        // These pairs have been counted twice
        pairs -= rec.second * (rec.second - 1) / 2;
    }

    printf("%lld\n", pairs);
    return 0;
}
