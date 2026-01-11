// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/344/problem/A

#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
#define mp make_pair
#define mt make_tuple
#define all(x) (x).begin(), (x).end()
#define FORN(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define FORR(i, n, step) for (int(i) = 0; (i) < (n); (i) += (step))
#define abs(x) (x < 0 ? (-x) : x)

#define ull unsigned long long int
#define ll long long int
#define vi vector<int>
#define vl vector<ll>
#define vu vector<ull>
#define vc vector<char>
#define pb push_back
#define MAXVAL(dt) std::numeric_limits<dt>::max()
#define MINVAL(dt) std::numeric_limits<dt>::min()

template <typename T> T input()
{
    T t;
    cin >> t;
    return t;
}
#define readn() input<ll>()
#define reads() input<string>()

template <typename T, typename... Args> void print(T v1, Args... v2)
{
    cout << v1;
    print(v2...);
}

template <typename T, typename... Args> void println(T v1, Args... v2)
{
    cout << v1;
    print(v2...);
    cout << "\n";
}

template <typename T> void print(T v1) { cout << v1; }

template <typename T> void println(T v1)
{
    cout << v1;
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n = readn();
    string s, prev = "  ";
    ll groups = 0;
    FORN(i, n)
    {
        s = reads();
        if (s[0] == prev[1])
        {
            groups++;
        }
        prev = s;
    }
    groups++;
    println(groups);
    return 0;
}
