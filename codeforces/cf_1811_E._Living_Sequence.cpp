// https://github.com/ananthvk/codeforces-solutions
// https://codeforces.com/contest/1811/problem/E
// Solution is from line 60
#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

// clang-format off
typedef unsigned long long int ull;
typedef long long int ll;
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
#define vi vector<int>
#define vl vector<ll>
#define vu vector<ull>
#define vc vector<char>
#define pb push_back
#define pf push_front
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
ull power(ull base, ull exponent)
{
    for (ull i = 1; i <= exponent; i++)
    {
        base *= base;
    }
    return base;
}
ull before(ull number, ull digits)
{
    // Get the count of numbers before this number
    if (number < 4)
    {
        return number - 1;
    }
    if (number < 10)
    {
        return number - 2;
    }
}
// clang-format off
ull table[] =
        {8,  // 8 * 9^0 -> Count of numbers with single digit and no 4
         72, // 8 * 9^1 -> Count of numbers with two digits and no 4s
         648, // 8 * 9^2
         5832, // 8 * 9^3
         52488, // and so on....
         472392,
         4251528,
         38263752,
         344373768,
         3099363912,
         27894275208,
         251048476872,
         2259436291848,
         20334926626632,
         183014339639688
        };

ull table2[] = {1,
                 9,
                 81,
                 729,
                 6561,
                 59049,
                 531441,
                 4782969,
                 43046721,
                 387420489,
                 3486784401,
                 31381059609,
                 282429536481,
                 2541865828329,
                 22876792454961

};
const ll table_length = sizeof(table)/sizeof(table[0]);
const ll table2_length = sizeof(table2)/sizeof(table2[0]);
// clang-format on

int main()
{
    FAST_IO
    ll nt = readn();
    FORN(i, nt)
    {
        ull n = input<ull>();
        ull sum = 0;
        ll index = 0;
        ll digits = 0;
        for (; digits < table_length; digits++)
        {
            if ((table[digits] + sum) > n)
            {
                digits++;
                break;
            }
            sum += table[digits];
        }
        println("*", sum, " ", n, " ", n-sum);
        n -= sum;
        for(ll k = table2_length-1; k > 0; k--){
            while((n >=table2[k])){
                n -= table2[k];
                sum +=  table2[k];
            }
        }
        println(">", sum, " ", n);
        for (ll i = digits; i > 0; i--)
        {
            ull factor = table2[(i-1)];
        }
    }
    return 0;
}
*/
// Editorial solution
#include <iostream>
#include <cmath>
#include <cctype>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <deque>
#include <stack>
#include <unordered_set>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <queue>
#include <unordered_map>
#include <random>
#include <cfloat>
#include <chrono>
#include <bitset>
#include <complex>
#include <immintrin.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int32_t num_tests;
    std::cin >> num_tests;

    for(int32_t t = 0; t < num_tests; t++) {
        int64_t k;
        std::cin >> k;

        std::vector<int32_t> digits;
        while(k > 0) {
            digits.push_back(k % 16);
            k /= 16;
        }

        println(digits);
        std::reverse(digits.begin(), digits.end());
        println(digits);

        /*
        for(int32_t i = 0; i < digits.size(); i++)
            std::cout << (char)(digits[i] < 4 ? (digits[i] + '0') : (digits[i] + '1'));
        std::cout << "\n";
        */
    }
    return 0;
}

