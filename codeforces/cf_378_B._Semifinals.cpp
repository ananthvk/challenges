// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/378/problem/B
// Solution is from line 61
#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <stdint.h>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

// clang-format off
typedef uint64_t ull;
typedef int64_t ll;
typedef struct {ll x; ll y;} pointi;
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define mp make_pair
#define mt make_tuple
// Looping construct macros
#define FORN(i, stop) for (ll(i) = 0; (i) < (stop); (i)++)
#define FORR(i, stop, step) for (ll(i) = 0; (i) < (stop); (i) += (step))
#define FORS(i, start, stop, step) for (ll(i) = (start); (i) < (stop); (i) += (step))
#define DONOTUSECONC(a, b) a##b
#define DONOTUSECON(a,b) DONOTUSECONC(a, b)
#define DONOTUSEENUMERATE(i, val, container, body, ite) ll i = 0; auto ite = container.begin(); decltype(container)::value_type val; for (; ite != container.end(); ite++, i++){ val = *ite; body }
// A macro for python-style enumerate, though it is not very neat
#define ENUMERATE(i, val, container, body) {DONOTUSEENUMERATE(i, val, container, body, DONOTUSECON(DONOTUSECON(container,iterator), __COUNTER__))}
#define abs(x) (x < 0 ? (-x) : x)
#define vi vector<int>
#define vl vector<ll>
#define vu vector<ull>
#define vc vector<char>
#define pb push_back
#define pf push_front
#define all(x) (x).begin(), (x).end()
// Maximum and minimum value of a datatype
// use it as MAXVAL(ll) - useful for finding minimum/maximum element, etc
#define MAXVAL(dt) std::numeric_limits<dt>::max()
#define MINVAL(dt) std::numeric_limits<dt>::min()
// Read a single value such as int, string, etc
#define readn() input<ll>()
#define reads() input<string>()
// Read a list of values after reading n, number of elements
// 'i' - integer, 'c' - character
#define readvi() readv<ll>()
#define readvc() readv<char>()
// Same as above, but when the number of elements is known
#define readvin(n) readv<ll>(n)
#define readvcn(n) readv<char>(n)
// Templated functions for input and output
template <typename T> ostream &operator<<(ostream &os, const deque<T> &v) { FORN(i, v.size()) { os << v[i]; if (i != (v.size() - 1)) os << " "; } return os; } template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) { FORN(i, v.size()) { os << v[i]; if (i != (v.size() - 1)) os << " "; } return os; } template <typename T> T input() { T t; cin >> t; return t; } template <typename T> vector<T> readv() { std::vector<T> t; ll n; cin >> n; t.reserve(n); FORN(i, n) { t.push_back(input<T>()); } return t; } template <typename T> vector<T> readv(ll n) { std::vector<T> t; t.reserve(n); FORN(i, n) { t.push_back(input<T>()); } return t; } template <typename T> void print(T v1) { cout << v1; } template <typename T> void println(T v1) { cout << v1; cout << "\n"; } template <typename T, typename... Args> void print(T v1, Args... v2) { cout << v1; print(v2...); } template <typename T, typename... Args> void println(T v1, Args... v2) { cout << v1; print(v2...); cout << "\n"; }
// Printing functions for debugging
#ifndef ONLINE_JUDGE
template <typename T> void dprint(T v1) { cerr << v1; } template <typename T> void dprintln(T v1) { cerr << v1; cerr << "\n"; } template <typename T, typename... Args> void dprint(T v1, Args... v2) { cerr << v1; dprint(v2...); } template <typename T, typename... Args> void dprintln(T v1, Args... v2) { cerr << v1; dprint(v2...); cerr << "\n"; }
#else
template <typename T> void dprint(T v1) { } template <typename T> void dprintln(T v1) {} template <typename T, typename... Args> void dprint(T v1, Args... v2) {} template <typename T, typename... Args> void dprintln(T v1, Args... v2) {}
#endif
// clang-format on
// Solution from here
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

int main()
{
    FAST_IO
    ll n = readn();
    vector<ll> av(n);
    vector<ll> bv(n);

    string ares(n, '0');
    string bres(n, '0');

    // Given in the description that the values are in sorted order
    FORN(i, n)
    {
        ll a = readn();
        ll b = readn();

        av[i] = a;
        bv[i] = b;
    }

    // An observation: All candidates upto n/2 will always get a chance to go to
    // the finals We have to only test for candidates after k = n/2
    /*
    FORN(i, (n/2))
    {
        ares[i] = '1';
        bres[i] = '1';
    }

    FORN(k, (n / 2)-2)
    {
        // Get the remaining n-2k participants using two pointers
        // Also ignore the first k participants in both a and b
        ll ia = k;
        ll ib = k;
        do{
            if(av[ia] < bv[ib]){
                ares[ia] = '1';
                ++ia;
            }
            else if(bv[ib] < av[ia]){
                bres[ib] = '1';
                ++ib;
            }
        }while(ia < n && ib < n);
    }
    */

    // When k = 0, we need to choose n members from both the list
    ll i = 0;
    ll j = 0;
    ll ele = 0;
    while (i < n && j < n && ele < n)
    {
        if(av[i] < bv[j]){
            ares[i] = '1';
            ++i;
            ++ele;
        }
        else if(bv[j] < av[i]){
            bres[j] = '1';
            ++j;
            ++ele;
        }
    }

    // When k = n/2, mark the first half elements
    FORN(i, (n/2))
    {
        ares[i] = '1';
        bres[i] = '1';
    }

    println(ares);
    println(bres);

    return 0;
}
