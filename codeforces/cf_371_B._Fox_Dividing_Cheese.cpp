#include <iostream>
#include <tuple>
#include <vector>

typedef std::tuple<int, int, int, int> x235;

x235 factorize(int number)
{
    int c2 = 0, c3 = 0, c5 = 0;
    while (number % 2 == 0)
    {
        c2 += 1;
        number /= 2;
    }
    while (number % 3 == 0)
    {
        c3 += 1;
        number /= 3;
    }
    while (number % 5 == 0)
    {
        c5 += 1;
        number /= 5;
    }
    return std::make_tuple(number, c2, c3, c5);
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int a, b;
    std::cin >> a >> b;
    auto fa = factorize(a);
    auto fb = factorize(b);
    if (std::get<0>(fa) != std::get<0>(fb))
    {
        std::cout << "-1\n";
    }
    else
    {
        int soln = std::abs(std::get<1>(fa) - std::get<1>(fb)) +
                   std::abs(std::get<2>(fa) - std::get<2>(fb)) +
                   std::abs(std::get<3>(fa) - std::get<3>(fb));
        std::cout << soln << "\n";
    }
    return 0;
}