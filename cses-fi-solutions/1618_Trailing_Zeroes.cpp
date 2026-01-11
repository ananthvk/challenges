#include <iostream>
#include <stdint.h>

// Count the number of multiple of 5's in the factorial
// Also count the multiples of powers of 5, for example in 51, there are 2 25's so it means that there are 4 5s

int main()
{
    int64_t n;
    std::cin >> n;
    int64_t answer = 0;
    for (int64_t p = 5; p <= n; p *= 5)
    {
        answer += n / p;
    }
    std::cout << answer << std::endl;
}