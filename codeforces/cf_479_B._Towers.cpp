// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/479/problem/B
// Solution is from line 61
#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <set>
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

struct Element
{
    ll index;
    ll value;
};
bool operator<(const Element& first, const Element& other){
    return first.value < other.value;
}

Element getmax(const std::multiset<Element> &m) { return *m.rbegin(); }
Element getmin(const std::multiset<Element> &m) { return *m.begin(); }

void change_max(std::multiset<Element> &m, ll count)
{
    // This removes the largest element and adds the largest element + count in
    // the set Takes O(2nlogn)
    auto iter = m.end();
    --iter;
    auto val = *iter;
    m.erase(iter);
    m.insert({val.index, val.value + count});
}
void change_min(std::multiset<Element> &m, ll count)
{
    // This removes the smallest element and adds the smallest element + count
    // in the set Takes O(2nlogn)
    auto iter = m.begin();
    auto val = *iter;
    m.erase(iter);
    m.insert({val.index, val.value + count});
}

int main()
{
    FAST_IO
    ll n = readn();
    ll k = readn();
    ll operations = 0;
    multiset<Element> heights;
    vector<pair<ll, ll>> results;

    // Read the numbers
    FORN(i, n)
    {
        ll tmp = readn();
        heights.insert({i, tmp});
    }
    // TODO: Handle case when the size is 1

    ll min_instability = MAXVAL(ll);

    while (getmax(heights).value != getmin(heights).value && operations < k &&
           getmax(heights).index != getmin(heights).index)
    {
        Element maxelem = getmax(heights);
        Element minelem = getmin(heights);

        // Greedy technique
        // Change the elements only if doing so reduces the instability
        if ((maxelem.value - minelem.value) <= min_instability)
        {
            results.push_back(make_pair(maxelem.index, minelem.index));
            // Decrease the max element by one and increase min element by one
            change_max(heights, -1);
            change_min(heights, 1);

            min_instability = getmax(heights).value - getmin(heights).value;
            ++operations;
        }
        else
        {
            break;
        }
    }
    if(min_instability == MAXVAL(ll)){
        // Loop has never run, so instability is 0
        min_instability = 0;
    }
    println(min_instability, " ", operations);
    for(const auto& p: results){
        println(p.first+1, " ", p.second+1);
    }
    return 0;
}