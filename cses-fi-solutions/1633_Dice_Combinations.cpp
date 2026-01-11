// In this problem, a number, n is given, we have to find the number of ways of throwing dices to
// get the required sum.
#include <iostream>
#include <vector>
const unsigned long long int MODCONSTANT =  1e9 + 7;

typedef long long int ll;

ll count(ll n, std::vector<ll> &memo_table)
{
    ll c = 0;
    // Base case
    if (n <= 1)
        return 1;

    if (memo_table[n] != -1)
        return memo_table[n];

    for (int i = 1; i <= 6; i++)
    {
        // Number of ways to roll (1, n-1), (2, n-2) ... (3, n-6)
        if ((n - i) >= 0)
            c = (c % MODCONSTANT ) + (count(n - i, memo_table)  % MODCONSTANT);
        else
            break;
    }

    memo_table[n] = c % MODCONSTANT;
    return memo_table[n];
}

int main()
{
    int t;
    std::cin >> t;
    std::vector<ll> memo_table(t + 1, -1);
    std::cout << count(t, memo_table) % MODCONSTANT << std::endl;
}