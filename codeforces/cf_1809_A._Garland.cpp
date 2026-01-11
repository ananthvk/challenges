#include <iostream>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // To take n number of test cases from input
    int num_tests;
    std::cin >> num_tests;
    std::string light;
    for (int tno = 0; tno < num_tests; tno++)
    {
        std::cin >> light;
    }
    return 0;
}