#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include<numeric>
#include <vector>

const std::string filename = "input.txt";

int main()
{
    std::string line;
    std::ifstream ifs(filename, std::ios::in);
    std::vector<int> v1, v2;
    int l1, l2;

    while (std::getline(ifs, line))
    {
        std::stringstream ss(line);
        ss >> l1 >> l2;
        v1.push_back(l1);
        v2.push_back(l2);
    }
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::transform(v1.begin(), v1.end(), v2.begin(), v1.begin(),
                   [](int x, int y) { return abs(x - y); });
    auto solution = std::accumulate(v1.begin(), v1.end(), 0);
    std::cout << solution << std::endl;
}