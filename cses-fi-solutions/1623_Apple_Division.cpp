#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <math.h>
#include <numeric>
#include <sstream>
#include <vector>

int main()
{
    int n;
    std::vector<long long int> numbers;
    std::string line;
    std::cin >> n;
    std::cin.ignore();
    std::getline(std::cin, line);


    std::stringstream ss(line);
    std::copy(std::istream_iterator<long long int>(ss), std::istream_iterator<long long int>(),
              std::back_inserter(numbers));

    // Total sum of all the apples
    long long int sum = 0;
    sum = std::accumulate(numbers.begin(), numbers.end(), sum);
    long long int solution = std::numeric_limits<long long int>::max();

    // Try all combinations (2^n), choosing the apples to put in one side
    for (long long int i = 0; i <= std::pow(2, numbers.size()); i++)
    {
        long long int current = 0;
        // Each bit in the number represents if the apple is chosen or not
        for (int j = 0; j < numbers.size(); j++)
        {
            if ((i >> j) & 0x1)
            {
                current += numbers[j];
            }
        }
        solution = std::min(solution, std::abs((sum - current) - current));
    }
    std::cout << solution << std::endl;
};
