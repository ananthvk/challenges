// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/1674/problem/B
#include <iostream>
#include <vector>
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // To take n number of test cases from input
    int num_tests;
    std::cin >> num_tests;
    char l1, l2;
    for (int tno = 0; tno < num_tests; tno++)
    {
        std::cin >> l1 >> l2;
        std::cout << (l1 - 97) * 25 + ((l2 < l1) ? (l2 - 97 + 1) : (l2 - 97))
                  << "\n";
    }
    return 0;
}
