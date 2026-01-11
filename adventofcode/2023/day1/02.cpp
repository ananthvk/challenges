#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string line;
    std::vector<std::string> search_list = {"0", // Dummy
                                            "one", "two",   "three", "four", "five",
                                            "six", "seven", "eight", "nine"};
    std::ifstream ifs("input.txt");
    int sum = 0;
    while (std::getline(ifs, line))
    {
        int N = line.size();
        std::vector<int> digits;
        for (int i = 0; i < N; i++)
        {
            if (isdigit(line[i]))
            {
                digits.push_back(line[i] - '0');
            }
            else
            {
                for (int j = 0; j < N; j++)
                {
                    for (int k = 1; k < search_list.size(); k++)
                    {
                        if (search_list[k] == line.substr(i, j))
                        {
                            digits.push_back(k);
                        }
                    }
                }
            }
        }
        sum += digits.front() * 10 + digits.back();
        std::cout << digits.front() * 10 + digits.back() << std::endl;
    }
    std::cout << "Answer: " << sum << std::endl;
    return 0;
}