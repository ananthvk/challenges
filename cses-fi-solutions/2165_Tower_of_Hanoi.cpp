#include <iostream>
#include <math.h>

void solution(int n, int s, int a, int d)
{
    // The recursive solution is as follows
    // First move n-1 disks from s to a
    // Then move the nth disk from s to d
    // Then move the n-1 disks from a to d
    if (n <= 0)
        return;
    solution(n - 1, s, d, a);
    std::cout << s << " " << d << std::endl;
    solution(n - 1, a, s, d);
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << std::pow(2, n) - 1 << std::endl;
    solution(n, 1, 2, 3);
}