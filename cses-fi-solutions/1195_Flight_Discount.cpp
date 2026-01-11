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
#include <math.h>
#include <numeric>
#include <queue>
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
#pragma GCC diagnostic ignored "-Wunused-result"
#define FILE_IO freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); freopen("debug.txt", "w", stderr);
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
#define DBG(x) do {dprint(#x, " = ", x);} while(false)
#define DBGLN(x) do {dprintln(#x, " = ", x);} while(false)
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

struct wedge{ll src; ll dst; ll weight;};
using wadj_list = std::vector<std::vector<wedge>>;
wedge readwedge() {wedge w; w.src = readn(); w.dst = readn(); w.weight = readn(); return w;}
using adj_list = std::vector<std::vector<int>>;
std::pair<ll, ll> readedge() {pair<ll, ll> result; result.first = readn(); result.second = readn(); return result;}

#pragma GCC diagnostic warning "-Wsign-conversion"
// clang-format on
// Solution from here
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#pragma GCC diagnostic ignored "-Wunused-parameter"

void solve(ll test_case_number)
{
    // https://grok.com/share/bGVnYWN5_25a81060-c7a2-4541-8b7e-d09a96cae7be

    auto n = readn();
    auto m = readn();
    wadj_list adj(n);
    FORN(i, m)
    {
        auto w = readwedge();
        --w.src;
        --w.dst;
        adj[w.src].push_back(w);
    }

    struct Vertex
    {
        ll cost;
        ll v;

        enum State
        {
            COUPON_USED,
            COUPON_UNUSED
        } state;

        // For Min-Heap
        bool operator<(const Vertex &other) const { return cost > other.cost; }
    };

    priority_queue<Vertex> pq;
    std::vector<bool> visited[2] = {
        std::vector<bool>(n),
        std::vector<bool>(n),
    };
    std::vector<ll> dist[2] = {std::vector<ll>(n, 10e15), std::vector<ll>(n, 10e15)};

    pq.push({0, 0, Vertex::State::COUPON_UNUSED});
    dist[Vertex::State::COUPON_UNUSED][0] = 0;
    dist[Vertex::State::COUPON_USED][0] = 0;

    while (!pq.empty())
    {
        auto vertex = pq.top();
        pq.pop();

        if (visited[vertex.state][vertex.v])
            continue;

        visited[vertex.state][vertex.v] = true;

        for (const auto &adjacent : adj[vertex.v])
        {
            // Perform edge relaxation if necessary
            if (vertex.state == Vertex::State::COUPON_USED)
            {
                // Coupon has already been used
                auto new_cost = vertex.cost + adjacent.weight;
                if (new_cost < dist[Vertex::State::COUPON_USED][adjacent.dst])
                {
                    dist[Vertex::State::COUPON_USED][adjacent.dst] = new_cost;
                    pq.push({new_cost, adjacent.dst, Vertex::State::COUPON_USED});
                }
            }
            else
            {
                // There are two possibilities, use the coupon, or do not use the coupon

                // Do not use the coupon now
                auto new_cost = vertex.cost + adjacent.weight;
                if (new_cost < dist[Vertex::State::COUPON_UNUSED][adjacent.dst])
                {
                    dist[Vertex::State::COUPON_UNUSED][adjacent.dst] = new_cost;
                    pq.push({new_cost, adjacent.dst, Vertex::State::COUPON_UNUSED});
                }

                // Use the coupon
                new_cost = vertex.cost + adjacent.weight / 2;
                if (new_cost < dist[Vertex::State::COUPON_USED][adjacent.dst])
                {
                    dist[Vertex::State::COUPON_USED][adjacent.dst] = new_cost;
                    pq.push({new_cost, adjacent.dst, Vertex::State::COUPON_USED});
                }
            }
        }
    }

    auto dist1 = dist[Vertex::State::COUPON_USED][n - 1];
    auto dist2 = dist[Vertex::State::COUPON_UNUSED][n - 1];
    println(min(dist1, dist2));
}

int main()
{
#ifdef FILE_IO_ENABLED
    FILE_IO
#endif
    FAST_IO
    ll num_test_cases = 1;
    FORN(i, num_test_cases) { solve(i + 1); }
    return 0;
}

#pragma GCC diagnostic warning "-Wunused-parameter"