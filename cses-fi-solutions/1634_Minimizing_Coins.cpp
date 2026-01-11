#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long int;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, x;
    cin >> n >> x;
    vector<ll> v;
    v.reserve(n);
    for (ll i = 0; i < n; i++)
    {
        ll t;
        cin >> t;
        v.push_back(t);
    }

    // Subproblem: Check if the sum of a subset of coins is equal to the desired sum
    // Recurrence relation: minimal_coins(n) = minimal_coins(n - i)
}
