// https://github.com/ananthvk/codeforces-solutions
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast,unroll-loops")
// Gives weird errors while compiling on my machine but seems to work on OJ
#pragma GCC target("avx2,tune=native")
#endif
#pragma GCC diagnostic warning "-Wunknown-pragmas"
#define FAST_IO_ENABLED
// https://codeforces.com/blog/entry/96344
#include <algorithm>
#include <chrono>
#include <deque>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <stdint.h>
#include <string>
#include <math.h>
#include <tuple>
#include <vector>
using namespace std;

// clang-format off
#pragma GCC diagnostic ignored "-Wsign-conversion"
typedef uint64_t ull;
typedef int64_t ll;
typedef struct {ll x; ll y;} pointi;
#ifdef FAST_IO_ENABLED
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#else
#define FAST_IO {}
#endif
#define FILE_IO freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
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
// Read n elements of the specifed datatype 'i' - integer, 'c' - character
#define readvin(n) readv<ll>(n)
#define readvcn(n) readv<char>(n)
#define readvsn(n) readv<string>(n)
// Templated functions for input and output
template <typename T> ostream &operator<<(ostream &os, const deque<T> &v) { FORN(i, v.size()) { os << v[i]; if (i != (v.size() - 1)) os << " "; } return os; } template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) { FORN(i, v.size()) { os << v[i]; if (i != (v.size() - 1)) os << " "; } return os; } template <typename T> T input() { T t; cin >> t; return t; } template <typename T> vector<T> readv(ll n) { std::vector<T> t; t.reserve(n); FORN(i, n) { t.push_back(input<T>()); } return t; } template <typename T> void print(T v1) { cout << v1; } template <typename T> void println(T v1) { cout << v1; cout << "\n"; } template <typename T, typename... Args> void print(T v1, Args... v2) { cout << v1; print(v2...); } template <typename T, typename... Args> void println(T v1, Args... v2) { cout << v1; print(v2...); cout << "\n"; }
// Printing functions for debugging
#ifndef ONLINE_JUDGE
#define DBG(x) do {print(#x, " = ", x);} while(false)
#define DBGLN(x) do {println(#x, " = ", x);} while(false)
template <typename T> void dprint(T v1) { cerr << v1; } template <typename T> void dprintln(T v1) { cerr << v1; cerr << "\n"; } template <typename T, typename... Args> void dprint(T v1, Args... v2) { cerr << v1; dprint(v2...); } template <typename T, typename... Args> void dprintln(T v1, Args... v2) { cerr << v1; dprint(v2...); cerr << "\n"; }
#else
#define DBG(x) {}
#define DBGLN(x) {}
template <typename T> void dprint(T v1) { } template <typename T> void dprintln(T v1) {} template <typename T, typename... Args> void dprint(T v1, Args... v2) {} template <typename T, typename... Args> void dprintln(T v1, Args... v2) {}
#endif
// https://codeforces.com/blog/entry/62393
// http://xorshift.di.unimi.it/splitmix64.c
struct safe_hash { static uint64_t splitmix64(uint64_t x) { x += 0x9e3779b97f4a7c15; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9; x = (x ^ (x >> 27)) * 0x94d049bb133111eb; return x ^ (x >> 31); } size_t operator()(uint64_t x) const { static const uint64_t RND = chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x + RND); } };
#define unordered_map do_not_use_directly_if_integer_unordered_map
#include<unordered_map>
#undef unordered_map
#pragma GCC diagnostic warning "-Wsign-conversion"
// clang-format on
// Solution from here
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-conversion"
void solve(ll test_case_number)
{
    // Check for adjacent zeros, if there any group of 2 or more adjacent zeros,
    // it is possible to get n operations, where n is the number of ones.
    // If there is only a single 0, we can get the answer in n - 1 operations
    // otherwise, if there are no zeros, n - 2 operations
    ll n = readn();
    ll m = readn();
    auto s = readvsn(n);
    ll ones = 0;
    bool adj_zeroes = false;
    bool single_zero = false;
    for (ll i = 0; i < n; ++i)
    {
        for (ll j = 0; j < m; ++j)
        {
            ones += s[i][j] - '0';
        }
    }
    ll min_one_count = 1e10;
    for (ll i = 0; i < n - 1; ++i)
    {
        for (ll j = 0; j < m - 1; ++j)
        {
            // From all L's find the one with the minimum number of ones, this will be the one
            // to remove first
            int one_count = s[i][j] + s[i + 1][j] + s[i][j + 1] + s[i + 1][j + 1] - 4 * '0';
            if (one_count != 0)
            {
                min_one_count = min(min_one_count, (ll)max((ll)1, (ll)one_count - 1));
            }
        }
    }
    if (ones == 0)
    {
        println("0");
    }
    else
    {
        println(1 + ones - min_one_count);
    }
}

int main()
{
    FAST_IO
    ll num_test_cases = readn();
    FORN(i, num_test_cases)
    {
#ifndef ONLINE_JUDGE
        dprintln("========== TEST CASE [", i + 1, "] ==========");
        auto start = std::chrono::high_resolution_clock::now();
#endif
        solve(i + 1);
#ifndef ONLINE_JUDGE
        auto end = std::chrono::high_resolution_clock::now();
        auto timing = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        dprintln("========== Took ", timing.count(), " ms ==========");
#endif
    }
    return 0;
}
#pragma GCC diagnostic warning "-Wunused-parameter"
// This is the solution for the problem from codeforces
// https://codeforces.com/contest/1720/problem/C
