#include <iostream>
#include <set>
#include <stdint.h>

int main()
{
    // Let the sum of each set be equal to k
    // Then 2 * k = Sum(Natural numbers upto n)
    // If the sum of n natural numbers is an odd number, it contradicts with
    // the left hand side, so it is not possible to split the numbers into two sets
    // if the sum of the numbers is odd.
    int64_t n;
    std::cin >> n;
    int64_t sum = (n) * (n + 1) / 2;
    if (sum % 2 != 0)
    {
        std::cout << "NO" << std::endl;
        return 0;
    }
    std::cout << "YES" << std::endl;
    int64_t k = sum / 2;
    // Now find two sets such the sum of each set is equal to k
    // It doesn't matter what numbers we choose as long as the sum of one set is equal to k
    // So start with n and keep adding numbers until it equals k
    // The numbers which were not included belong to the second set
    std::set<int64_t> set1;
    for (int64_t i = n; i >= 1; i--)
    {
        if (k - i < 0)
            continue;
        k -= i;
        set1.insert(i);
        if (k == 0)
            break;
    }
    std::cout << set1.size() << std::endl;
    for (const auto &c : set1)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl
              << n - set1.size() << std::endl;
    for (int i = 1; i <= n; i++)
    {
        if (set1.find(i) == set1.end())
        {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}