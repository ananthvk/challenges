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
struct element
{
    ll a;
    ll b;
};
void solve(ll test_case_number)
{
    // Here's my solution
    // First create a vector of structs containing two corresponding elements of the arrays
    // Sort this vector with element as key
    // Perform a stable sort on this vector with element as key
    // If both a and b are in non decreasing order, the answer exists, else print -1
    // ???
    // Display the number of swaps required along with the swaps.
    ll n = readn();
    auto a = readvin(n);
    auto b = readvin(n);
    vector<element> elements;
    elements.reserve(n);
    FORN(i, n)
    {
        elements.push_back({a[i], b[i]});
    }
    /*
    sort(all(elements), [](const element &l, const element &r)
         { return l.a < r.a; });
    stable_sort(all(elements), [](const element &l, const element &r)
                { return l.b < r.b; });
    if (is_sorted(elements.begin(), elements.end(), [](const element &l, const element &r)
                  { return l.a < r.a; }) &&
        is_sorted(elements.begin(), elements.end(), [](const element &l, const element &r)
                  { return l.b < r.b; }))
    {
        println("POSSIBLE");
    }
    else
    {
        println("-1");
    }
    */
    // Try using bubble sort
    vector<element> answer;
    bool swapped = true;
    ll k = n;
    ll swaps = 0;
    while (swapped)
    {
        swapped = false;
        FORS(i, 1, k, 1)
        {
            if (elements[i - 1].a > elements[i].a)
            {
                swapped = true;
                ++swaps;
                swap(elements[i - 1], elements[i]);
                answer.push_back({i + 1, i + 1 - 1});
            }
        }
        --k;
    }
    swapped = true;
    k = n;
    while (swapped)
    {
        swapped = false;
        FORS(i, 1, k, 1)
        {
            if (elements[i - 1].a == elements[i].a && elements[i - 1].b > elements[i].b)
            {
                swapped = true;
                ++swaps;
                swap(elements[i - 1], elements[i]);
                answer.push_back({i + 1, i + 1 - 1});
            }
        }
        --k;
    }
    if (is_sorted(elements.begin(), elements.end(), [](const element &l, const element &r)
                  { return l.a < r.a; }) &&
        is_sorted(elements.begin(), elements.end(), [](const element &l, const element &r)
                  { return l.b < r.b; }))
    {
        println(swaps);
        for (const auto &e : answer)
        {
            println(e.a, " ", e.b);
        }
    }
    else
    {
        println("-1");
    }
}

int main()
{
    FAST_IO
    ll num_test_cases = readn();
    FORN(i, num_test_cases)
    {
        dprintln("========== TEST CASE [", i + 1, "] ==========");
        dprintln("");
        solve(i + 1);
    }
    return 0;
}
#pragma GCC diagnostic warning "-Wunused-parameter"
// This is the solution for the problem from codeforces
// https://codeforces.com/contest/1681/problem/C
