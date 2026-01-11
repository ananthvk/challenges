#include <iostream>
#include <stdint.h>

uint64_t total_number_of_ways(uint64_t k)
{
    // The total numer of ways to place two knights in a chess board:
    // First place one knight, there is k**2 number of ways
    // Then for the second knight, there is k**2 - 1 number of ways
    // Since both the knights are identical, divide the product by 2!
    return (k * k) * ((k * k) - 1) / 2;
}

uint64_t num_attack(uint64_t k)
{
    // Return the number of ways in which two knights can attack each other on a k*k chessboard
    // Divide the chess board into 2 x 3 cells. In each 2 x 3, the knights can attack each other in just two ways
    // Consider in both horizontal and vertical direction, so multiply by two
    if(k >= 3)
        return 2 * 2 * (k - 1) * (k - 2);
    return 0;
}

uint64_t solution(uint64_t k)
{
    return total_number_of_ways(k) - num_attack(k);
}

int main()
{
    int n;
    std::cin >> n;
    for (int k = 1; k <= n; k++)
    {
        std::cout << solution(k) << std::endl;
    }
}