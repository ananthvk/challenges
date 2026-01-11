// https://cses.fi/problemset/task/1071/
#include <algorithm>
#include <math.h>
#include <deque>
#include <numeric>
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
#ifdef ONLINE_JUDGE
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#else
#define FAST_IO ;
#endif
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
ll solution(ll y, ll x)
{

    if (x <= y)
    {
        // The column is to the left of the principal diagonal, so the result will be calculated with
        // the diagonal of the row of the query.
        // In odd rows, the flow of numbers is from left to right
        // In even rows, the flow of numbers is from right to left
        ll row_diagonal = 1 + y * (y - 1);
        if (y % 2 != 0)
        {
            return row_diagonal - (y - x);
        }
        else
        {
            return row_diagonal + (y - x);
        }
    }
    else
    {
        // The column is to the right of the principal diagonal, so the result will be calculated with
        // the diagonal of the column of the query.
        // In even columns, the flow of numbers is from top to bottom
        // In odd columns, the flow of numbers is from bottom to top
        ll column_diagonal = 1 + x * (x - 1);
        if (x % 2 != 0)
        {
            return column_diagonal + (x - y);
        }
        else
        {
            return column_diagonal - (x - y);
        }
    }
}
int main()
{
    FAST_IO
    ll t = readn();
    FORN(i, t)
    {
        ll y = readn();
        ll x = readn();
        // Solution:
        // On observing the diagonal elements, it is seen that they are in a series with varying difference in AP
        // of even numbers
        // 1   3   7   13   21   31   43
        //   2   4   6    8    10   12   .....

        // General formula for AP: Tn = a + (n-1)d
        // Then (n-1)d term represents the addition of all the common differences, since they are same,
        // It can be written as a multiplication

        // Tn = a + S_{n-1}, Where S_{n-1} is the sum of n-1 terms of the difference AP
        // Tn = a + (n-1)(2a' + (n-1-1)d)/2
        // For a = 1, a' = 2, d = 2
        // Tn = 1 + (n-1)(4 + 2n - 4)/2
        // Tn = 1 + n(n-1)
        // Gives the value of the diagonal element of the nth row or the nth column

        println(solution(y, x));
    }
    return 0;
}
