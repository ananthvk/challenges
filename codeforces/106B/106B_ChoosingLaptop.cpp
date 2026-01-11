// https://github.com/ananthvk/codeforces-solutions
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
/*
#ifdef ONLINE_JUDGE
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#else
#define FAST_IO {}
#endif
*/
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
struct spec
{
    ll speed;
    ll ram;
    ll hdd;
    ll cost;
    ll id;
    bool outdated;
};

int main()
{
    FAST_IO
    ll n = readn();
    vector<spec> specs;
    specs.reserve(n);
    FORN(sn, n)
    {
        spec s;
        s.speed = readn();
        s.ram = readn();
        s.hdd = readn();
        s.cost = readn();
        s.id = sn + 1;
        s.outdated = false;
        specs.push_back(s);
    }
    // n^2 is acceptable since n <= 100, so 10^4
    for (auto &test_spec : specs)
    {
        for (const auto &other : specs)
        {
            if (test_spec.speed < other.speed && test_spec.ram < other.ram && test_spec.hdd < other.hdd)
            {
                test_spec.outdated = true;
            }
        }
    }
    vector<spec> valid;
    // Remove copy if copies elements for which the predicate returns false
    remove_copy_if(specs.begin(), specs.end(), back_inserter(valid), [](const spec &s)
                   { return s.outdated; });
    sort(valid.begin(), valid.end(), [](const spec &l, const spec &r)
         { return l.cost < r.cost; });
    println(valid.front().id);
    return 0;
}
// This is the solution for the problem from codeforces
// https://codeforces.com/contest/106/problem/B
