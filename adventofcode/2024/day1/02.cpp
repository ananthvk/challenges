#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
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

    auto counts = std::accumulate(v2.begin(), v2.end(), std::map<int, int>(),
                                  [](std::map<int, int> &mp, int num)
                                  {
                                      ++mp[num];
                                      return mp;
                                  });
    auto solution = std::transform_reduce(v1.begin(), v1.end(), 0, std::plus<>{}, // Reduction
                                          [&counts](int value) { return value * counts[value]; });
    std::cout << solution << std::endl;
}