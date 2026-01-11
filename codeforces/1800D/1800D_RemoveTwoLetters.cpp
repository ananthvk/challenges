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
template <typename T> void dprint(T v1) { cerr << v1; } template <typename T> void dprintln(T v1) { cerr << v1; cerr << "\n"; } template <typename T, typename... Args> void dprint(T v1, Args... v2) { cerr << v1; dprint(v2...); } template <typename T, typename... Args> void dprintln(T v1, Args... v2) { cerr << v1; dprint(v2...); cerr << "\n"; }
#else
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
    // In this problem we have to find out the total number of _unique_ strings which can be formed by removing any two consecutive characters.
    // Consider the following example,
    // Let the string s be
    // ```
    // g g g g a x a y y y
    // 0 1 2 3 4 5 6 7 8 9
    // ```
    // Now if we remove the characters with index `4` and `5` or we remove the characters with index `5` and `6`, there is no difference, it does not matter what characters is at index `5`.
    // If we remove characters at index 4 and 5, we get
    // ```
    // g g g g a y y y
    // 0 1 2 3 6 7 8 9
    // ```
    // If we instead remove the characters at index 5 and 6, we get
    // ```
    // g g g g a y y y
    // 0 1 2 3 4 7 8 9
    // ```
    // Note that the strings obtained in both cases are same.
    // Also the number of pairs which are possible in a string of length $n$ is $n-1$ .
    // So for every i, if $s[i] == s[i+2]$ , decrease one from the total possible strings.
    ll n = readn();
    auto s = reads();
    ll answer = n - 1;
    FORS(i, 0, n - 1, 1)
    {
        answer -= s[i] == s[i + 2];
    }
    println(answer);
}


int main()
{
    FAST_IO
    ll num_test_cases = readn();
    FORN(i, num_test_cases)
    {
        solve(i + 1);
    }
    return 0;
}
#pragma GCC diagnostic warning "-Wunused-parameter"
// This is the solution for the problem from codeforces
// https://codeforces.com/contest/1800/problem/D
