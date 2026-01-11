#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>
#include <stdint.h>
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
//#define abs(x) (x < 0 ? (-x) : x)
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
/*
int main()
{
    FAST_IO
    ll ntests = readn();
    FORN(i, ntests)
    {
        ll n = readn();
        auto v = readvin(n);
        // 1 is guaranteed to exist in the sequence
        auto pos1 = find(v.begin(), v.end(), 1);
        auto posn = find(v.begin(), v.end(), n);
        // Find the smallest element next to 1
        ll a = MAXVAL(ll);
        ll b = MAXVAL(ll);
        if (pos1 + 1 != v.end())
        {
            a = *(pos1 + 1);
        }
        if (pos1 != v.begin())
        {
            b = *(pos1 - 1);
        }
        ll minv = min(a, b);

        if (posn == pos1 + 1 && pos1 == v.begin())
        {
        }
        else if (posn == pos1 + 1 || (pos1 != v.begin() && (pos1 - 1) == posn))
        {
            // Largest element is already adjacent to this element
            // Take the next largest element
            posn = find(v.begin(), v.end(), n - 1);
        }
        if (minv == a)
        {
            // Swap position of 1 + 1 with position of n
            println(posn - v.begin() + 1, " ", pos1 - v.begin() + 1 + 1);
        }
        else
        {
            println(posn - v.begin() + 1, " ", pos1 - v.begin() - 1 + 1);
        }
    }
    return 0;
}
*/

int main()
{
    FAST_IO
    ll ntests = readn();
    FORN(nt, ntests)
    {
        ll n = readn();
        auto v = readvin(n);
        // Find the position of the largest element
        auto posn = find(all(v), n);
        auto pos1 = find(all(v), 1);
        auto pos2 = find(all(v), 2);
        long a, b;

        if ((pos1 < posn && pos2 > posn) || (pos2 < posn && pos1 > posn))
        {
            a = pos1 - v.begin() + 1;
            b = pos2 - v.begin() + 1;
        }
        else if (pos1 > posn && pos2 > posn)
        {
            a = min(pos1 - v.begin(), pos2 - v.begin()) + 1;
            b = posn - v.begin() + 1;
        }
        else{
            a = max(pos1 - v.begin(), pos2 - v.begin()) + 1;
            b = posn - v.begin() + 1;
        }
        println(a, " ", b);
    }
    return 0;
}
// This is the solution for the problem from codeforces
// https://codeforces.com/contest/1838/problem/B
