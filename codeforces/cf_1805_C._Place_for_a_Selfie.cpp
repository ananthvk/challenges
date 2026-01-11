// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/1805/problem/C
#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <math.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
using namespace std;
#define mp make_pair
#define mt make_tuple
#define all(x) (x).begin(), (x).end()
#define FORN(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define FORR(i, n, step) for (int(i) = 0; (i) < (n); (i) += (step))
#define abs(x) (x < 0 ? (-x) : x)
#define ull unsigned long long int
#define ll long long int
#define vi vector<int>
#define vl vector<ll>
#define vu vector<ull>
#define vc vector<char>
#define pb push_back
#define pf push_front
#define MAXVAL(dt) std::numeric_limits<dt>::max()
#define MINVAL(dt) std::numeric_limits<dt>::min()
#define readn() input<ll>()
#define reads() input<string>()
#define readvi() readv<ll>()
#define readvc() readv<char>()
#define readvin(n) readv<ll>(n)
#define readvcn(n) readv<char>(n)

template <typename T> ostream &operator<<(ostream &os, const vector<T> &v)
{
    FORN(i, v.size())
    {
        os << v[i];
        if (i != (v.size() - 1))
        {
            os << " ";
        }
    }
    return os;
}
template <typename T> T input()
{
    T t;
    cin >> t;
    return t;
}
template <typename T> vector<T> readv()
{
    std::vector<T> t;
    ll n;
    cin >> n;
    t.reserve(n);
    FORN(i, n) { t.push_back(input<T>()); }
    return t;
}
template <typename T> vector<T> readv(ll n)
{
    std::vector<T> t;
    t.reserve(n);
    FORN(i, n) { t.push_back(input<T>()); }
    return t;
}
template <typename T> void print(T v1) { cout << v1; }
template <typename T> void println(T v1)
{
    cout << v1;
    cout << "\n";
}
template <typename T, typename... Args> void print(T v1, Args... v2)
{
    cout << v1;
    print(v2...);
}
template <typename T, typename... Args> void println(T v1, Args... v2)
{
    cout << v1;
    print(v2...);
    cout << "\n";
}
#ifndef ONLINE_JUDGE
template <typename T> void dprint(T v1) { cerr << v1; }
template <typename T> void dprintln(T v1)
{
    cerr << v1;
    cerr << "\n";
}
template <typename T, typename... Args> void dprint(T v1, Args... v2)
{
    cerr << v1;
    dprint(v2...);
}
template <typename T, typename... Args> void dprintln(T v1, Args... v2)
{
    cerr << v1;
    dprint(v2...);
    cerr << "\n";
}
#else
template <typename T> void dprint(T v1) {}
template <typename T> void dprintln(T v1) {}
template <typename T, typename... Args> void dprint(T v1, Args... v2) {}
template <typename T, typename... Args> void dprintln(T v1, Args... v2) {}
#endif

double get_disc(ll a, ll b, ll c) { return b * b - 4 * a * c; }

pair<bool, pair<double, double>> get_soln(ll a, ll b, ll c)
{
    double disc = get_disc(a, b, c);
    if (disc < 0)
    {
        return mp(false, mp(0, 0));
    }
    double disc_rt = sqrt(disc);
    return mp(true, mp((-b - disc_rt) / (2 * a), (-b + disc_rt) / (2 * a)));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll ntests = readn();
    FORN(test_no, ntests)
    {
        ll n = readn();
        ll m = readn();
        auto k = readvin(n);
        vector<tuple<int, int, int>> parameters;
        parameters.reserve(m);
        FORN(i, m) { parameters.push_back(mt(readn(), readn(), readn())); }
        ll index = 0;
        std::sort(all(k));
        for (const auto &parabola : parameters)
        {
            ll a = get<0>(parabola);
            ll b = get<1>(parabola);
            ll c = get<2>(parabola);
            bool flag = false;
            // dprintln(a, " ", b, " ", c);
            auto solution = get_soln(1, -2 * b, (b * b - 4 * a * c));
            if (!solution.first)
            {
                println("NO");
                continue;
            }

            ll lb = 0;
            ll ub = k.size() - 1;
            ll mid;
            while (lb <= ub)
            {
                mid = (lb + ub) / 2;
                if (solution.second.second <= k[mid])
                {
                    ub = mid - 1;
                }
                else if (solution.second.first >= k[mid])
                {
                    lb = mid + 1;
                }
                else
                {
                    // solution.second.first < k[mid] and
                    // solution.second.second > k[mid]
                    println("YES");
                    println(k[mid]);
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                println("NO");
            }
            // dprintln("Solution: ", solution.second.first, " ",
            // solution.second.second);
            /*
            if(!solution.first){
                println("NO");
            }
            else{
                bool flag = false;
                for(const auto&k1: k){
                    if(k1 > solution.second.first && k1 <
            solution.second.second){ println("YES"); println(k1); flag = true;
                        break;
                    }
                }
                if(!flag){
                    println("NO");
                }
            }
            */
        }
    }
    return 0;
}