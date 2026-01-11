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
#include <math.h>
#include <map>
#include <numeric>
#include <set>
#include <stdint.h>
#include <string>
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
void solve(ll test_case_number)
{
    // Adopt a lazy approach as it will take too much time to reset all elements for every query
    ll n = readn();
    ll q = readn();
    auto a = readvin(n);
    ll sum = accumulate(a.begin(), a.end(), (ll)0);
    vl fill_ids(n, 0);
    ll current_fill_id = 0;
    ll current_fill = 0;
    for (ll i = 1; i <= q; ++i)
    {
        ll t = readn();
        if (t == 1)
        {
            ll i = readn();
            ll x = readn();
            if (fill_ids[i - 1] == current_fill_id)
            {
                // This operation is performed after a type 2 operation
                ll diff = x - a[i - 1];
                sum += diff;
                a[i - 1] = x;
            }
            else
            {
                ll diff = x - current_fill;
                sum += diff;
                a[i - 1] = x;
                fill_ids[i - 1] = current_fill_id;
            }
            println(sum);
        }
        else
        {
            ll x = readn();
            sum = x * n;
            println(sum);
            current_fill_id = i;
            current_fill = x;
        }
    }
}

int main()
{
    FAST_IO
    FORN(i, 1)
    {
        solve(i + 1);
    }
    return 0;
}
#pragma GCC diagnostic warning "-Wunused-parameter"
// This is the solution for the problem from codeforces
// https://codeforces.com/contest/1679/problem/B
