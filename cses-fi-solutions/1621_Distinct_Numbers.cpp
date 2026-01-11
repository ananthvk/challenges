#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <set>
using namespace std;
int main()
{
    int n;
    set<int> v;
    cin >> n;
    cin.ignore();
    string line;
    getline(std::cin, line);
    stringstream ss(line);
    for_each(std::istream_iterator<int>(ss), istream_iterator<int>(),
                  [&v](int x) { v.insert(x); });
    cout << v.size() << std::endl;
}