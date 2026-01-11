// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/304/problem/C
#include <iostream>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    if (n % 2 == 0)
    {
        std::cout << "-1\n";
        return 0;
    }

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (j == 2)
            {
                std::cout << (2 * i) % n;
                if (i != n - 1)
                {
                    std::cout << " ";
                }
            }
            else
            {
                std::cout << i;
                if (i != n - 1)
                {
                    std::cout << " ";
                }
            }
        }
        std::cout << "\n";
    }

    // Now our aim is to find a permutation of numbers such that no two ai + bi
    // % n are equal
    return 0;
}
