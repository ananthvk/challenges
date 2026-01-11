#include <iostream>
#include <stdint.h>

// Consider that we perform 'm' moves of 1 coin left pile, 2 coin right pile
// and 'n' moves of 2 coin left pile, 1 coin right pile
// We can model this situation as simulatenous equation, with (1, 2) + (2, 1) = (a, b)
// m + 2n = a
// 2m + n = b
// If we have to empty the piles, there should be a positive integral solution to the above equations
// On solving, we get n = 1/3 (2a - b), m = 1/3 (2b - a)

int main()
{
    int64_t t, a, b;
    std::cin >> t;
    while (t--)
    {
        std::cin >> a >> b;
        int64_t s1 = 2 * a - b;
        int64_t s2 = 2 * b - a;
        if (s1 % 3 == 0 && s2 % 3 == 0 && s1 >= 0 && s2 >= 0)
        {
            std::cout << "YES" << std::endl;
        }
        else
        {
            std::cout << "NO" << std::endl;
        }
    }
}
