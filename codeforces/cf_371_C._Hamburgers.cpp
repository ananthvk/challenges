// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/371/problem/C
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
#define pf push_front
#define f front()
#define b back()
#define MAXVAL(dt) std::numeric_limits<dt>::max()
#define MINVAL(dt) std::numeric_limits<dt>::min()
#define readn() input<ll>()
#define reads() input<string>()
#define readvi() readv<ll>()
#define readvc() readv<char>()
#define readvin(n) readv<ll>(n)
#define readvcn(n) readv<char>(n)

template <typename T> ostream &operator<<(ostream &os, const vector<T> &v)
{
    FORN(i, v.size())
    {
        os << v[i];
        if (i != (v.size() - 1))
        {
            os << " ";
        }
    }
    return os;
}

template <typename T> T input()
{
    T t;
    cin >> t;
    return t;
}
template <typename T> vector<T> readv()
{
    std::vector<T> t;
    ll n;
    cin >> n;
    t.reserve(n);
    FORN(i, n) { t.push_back(input<T>()); }
    return t;
}
template <typename T> vector<T> readv(ll n)
{
    std::vector<T> t;
    t.reserve(n);
    FORN(i, n) { t.push_back(input<T>()); }
    return t;
}
template <typename T> void print(T v1) { cout << v1; }
template <typename T> void println(T v1)
{
    cout << v1;
    cout << "\n";
}
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

#ifndef ONLINE_JUDGE
template <typename T> void dprint(T v1) { cerr << v1; }
template <typename T> void dprintln(T v1)
{
    cerr << v1;
    cerr << "\n";
}
template <typename T, typename... Args> void dprint(T v1, Args... v2)
{
    cerr << v1;
    dprint(v2...);
}
template <typename T, typename... Args> void dprintln(T v1, Args... v2)
{
    cerr << v1;
    dprint(v2...);
    cerr << "\n";
}
#else
template <typename T> void dprint(T v1) {}
template <typename T> void dprintln(T v1) {}
template <typename T, typename... Args> void dprint(T v1, Args... v2) {}
template <typename T, typename... Args> void dprintln(T v1, Args... v2) {}
#endif
// ========================================================================
// ALGORITHM
// 1. With the recipe and number of items in kitchen, find the number of
//    burgers made
// 2. Also find the remainder, or the number of items left unused.

struct burger_count
{
    ll bread;
    ll sausage;
    ll cheese;
};

burger_count read_recipe()
{
    string line;
    burger_count bc = {0, 0, 0};

    cin >> line;
    for (const auto &ch : line)
    {
        if (ch == 'B')
        {
            bc.bread++;
        }
        else if (ch == 'C')
        {
            bc.cheese++;
        }
        else if (ch == 'S')
        {
            bc.sausage++;
        }
    }
    return bc;
}

burger_count read_count()
{
    burger_count bc;
    std::cin >> bc.bread;
    std::cin >> bc.sausage;
    std::cin >> bc.cheese;
    return bc;
}

ll cost(ll x, burger_count recipe, burger_count price, burger_count in_kitchen)
{
    // Returns the cost to make x burgers
    ll breads = std::max({(ll)0, recipe.bread * x - in_kitchen.bread});
    ll sausages = std::max({(ll)0, recipe.sausage * x - in_kitchen.sausage});
    ll cheese = std::max({(ll)0, recipe.cheese * x - in_kitchen.cheese});
    return breads * price.bread + sausages * price.sausage +
           cheese * price.cheese;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto items_to_make_one = read_recipe();
    auto in_kitchen = read_count();
    auto price = read_count();
    auto cash = readn();

    ll lb = 0;
    ll ub = 1000000000000 + 1000; // 10^12
    ll max_burgers = 0;

    while (lb <= ub)
    {
        ll mid = lb + (ub - lb) / 2;
        ll estimate = cost(mid, items_to_make_one, price, in_kitchen);
        if (estimate > cash)
        {
            ub = mid - 1;
        }
        else if (estimate < cash)
        {
            if (mid > max_burgers)
            {
                max_burgers = mid;
            }
            lb = mid + 1;
        }
        else
        {
            max_burgers = mid;
            break;
        }
    }
    println(max_burgers);
}
