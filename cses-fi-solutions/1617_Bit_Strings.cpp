#include <iostream>
#define MODULO (1000000000 + 7)
int main()
{
    int n;
    std::cin >> n;
    int64_t prod = 1;
    while (n--)
        prod = (prod * 2) % MODULO;
    std::cout << prod <<  std::endl;
}