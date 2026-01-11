#include <fstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

long long int num_solutions(long long int a, long long int b, long long int c)
{
    double d = b * b - 4 * a * c;
    if (d > 0)
    {
        double x1 = (-b + std::sqrt(d)) / (2.0 * a);
        double x2 = (-b - std::sqrt(d)) / (2.0 * a);
        long long int solution = (long long int)std::abs((std::floor(x1) - std::floor(x2)));
        if (std::trunc(x1) == x1)
        {
            // Both are long long integral roots
            // Do not include them in the final solution
            solution -= 1;
        }
        return solution;
    }
    return 0;
}

int main()
{
    std::ifstream ifs("input2.txt");
    std::string line1, line2;
    std::vector<long long int> times;
    std::vector<long long int> distances;

    std::getline(ifs, line1);
    std::getline(ifs, line2);
    std::stringstream ss1(line1.substr(line1.find(':') + 1));
    std::stringstream ss2(line2.substr(line2.find(':') + 1));

    std::copy(std::istream_iterator<long long int>(ss1), std::istream_iterator<long long int>(),
              std::back_inserter(times));
    std::copy(std::istream_iterator<long long int>(ss2), std::istream_iterator<long long int>(),
              std::back_inserter(distances));

    // Using a few mathematical transformations,
    // The total distance travelled = (t - t1) * t1, t1 = time for which the button was held
    // The inequality is given as a quadratic equation (t - t1) * t1 - d > 0
    // Find the two roots of the quadratic equation, then find the number of long long integers between them
    // That gives the solution
    // Also if the distances are equal, we do not win since it is a draw. So exclude solutions which
    // have b^2 = 4ac

    std::vector<long long int> solutions;
    for (size_t i = 0; i < times.size(); i++)
    {
        solutions.push_back(num_solutions(-1, times[i], -distances[i]));
    }
    long long int answer = std::accumulate(solutions.begin(), solutions.end(), 1, std::multiplies<long long int>());
    std::cout << "Answer: " << answer << std::endl;
}