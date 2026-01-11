// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/1798/problem/A
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

bool solution_exists(vector<ll> v1, vector<ll> v2)
{
    auto maxv1 = v1.back();
    auto maxv2 = v2.back();
    for (int i = 0; i < v1.size() - 1; i++)
    {
        if (v1[i] > maxv1)
        {
            if (v2[i] <= maxv1 && v1[i] <= maxv2)
            {
                auto tmp = v1[i];
                v1[i] = v2[i];
                v2[i] = tmp;
            }
            else
            {
                return false;
            }
        }
        if (v2[i] > maxv2)
        {
            if (v1[i] <= maxv2 && v2[i] <= maxv1)
            {
                auto tmp = v1[i];
                v1[i] = v2[i];
                v2[i] = tmp;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = readn();
    FORN(i, n)
    {
        auto n = readn();
        auto v1 = readvin(n);
        auto v2 = readvin(n);
        if (solution_exists(v1, v2) || solution_exists(v2, v1))
        {
            println("YES");
        }
        else
        {
            println("NO");
        }
    }
    return 0;
}