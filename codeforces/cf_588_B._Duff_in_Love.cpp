// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/588/problem/B
#include <cmath>
#include <iostream>
#include <vector>
typedef unsigned long long int ull;
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    ull n;
    std::cin >> n;
    ull answer = 1;
    ull divisor = 2;
    bool first = true;
    ull k = 1;
    ull original_n = n;
    bool subtract = true;

    while (n > 1)
    {
        first = true;
        while (n % divisor == 0)
        {
            // std::cout<<divisor<<" ";
            if (first)
            {
                answer *= divisor;
            }
            n /= divisor;
            first = false;
        }
        if (divisor > sqrt(n))
        {
            if (original_n % n == 0)
            {
                // std::cout<<n<<" ";
                answer *= n;
            }
            break;
        }
        if (divisor > 3)
        {
            divisor = 6 * k + ((subtract) ? -1 : 1);
            subtract = !subtract;
            if (subtract)
            {
                k++;
            }
        }
        else
        {
            divisor += 1;
        }
    }
    // std::cout<<"\n";
    std::cout << answer << "\n";
}