#include <fstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int num_solutions(int a, int b, int c)
{
    double d = b * b - 4 * a * c;
    if (d > 0)
    {
        double x1 = (-b + std::sqrt(d)) / (2.0 * a);
        double x2 = (-b - std::sqrt(d)) / (2.0 * a);
        int solution = (int)std::abs((std::floor(x1) - std::floor(x2)));
        if (std::trunc(x1) == x1)
        {
            // Both are integral roots
            // Do not include them in the final solution
            solution -= 1;
        }
        return solution;
    }
    return 0;
}

int main()
{
    std::ifstream ifs("input.txt");
    std::string line1, line2;
    std::vector<int> times;
    std::vector<int> distances;

    std::getline(ifs, line1);
    std::getline(ifs, line2);
    std::stringstream ss1(line1.substr(line1.find(':') + 1));
    std::stringstream ss2(line2.substr(line2.find(':') + 1));

    std::copy(std::istream_iterator<int>(ss1), std::istream_iterator<int>(),
              std::back_inserter(times));
    std::copy(std::istream_iterator<int>(ss2), std::istream_iterator<int>(),
              std::back_inserter(distances));

    // Using a few mathematical transformations,
    // The total distance travelled = (t - t1) * t1, t1 = time for which the button was held
    // The inequality is given as a quadratic equation (t - t1) * t1 - d > 0
    // Find the two roots of the quadratic equation, then find the number of integers between them
    // That gives the solution
    // Also if the distances are equal, we do not win since it is a draw. So exclude solutions which
    // have b^2 = 4ac

    std::vector<int> solutions;
    for (size_t i = 0; i < times.size(); i++)
    {
        solutions.push_back(num_solutions(-1, times[i], -distances[i]));
    }
    int answer = std::accumulate(solutions.begin(), solutions.end(), 1, std::multiplies<int>());
    std::cout << "Answer: " << answer << std::endl;
}