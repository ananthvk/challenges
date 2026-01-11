#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

int main()
{
    std::ifstream ifs("input.txt");
    std::string line;
    int sum = 0;
    while (std::getline(ifs, line))
    {
        auto new_end = std::remove_if(line.begin(), line.end(), [](char x) { return isalpha(x); });
        sum += (line[0] - '0') * 10 + (*(new_end - 1) - '0');
    }
    std::cout << "Answer: " << sum << std::endl;
    return 0;
}