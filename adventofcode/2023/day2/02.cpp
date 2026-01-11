#include <fstream>
#include <iostream>
#include <limits.h>
#include <sstream>

struct max_struct
{
    int red;
    int green;
    int blue;
};

max_struct get_powerset_record(const std::string &record)
{
    std::stringstream ss(record);
    std::string token;
    int max_red = 0;
    int max_blue = 0;
    int max_green = 0;

    while (std::getline(ss, token, ','))
    {
        std::string color;
        int count;
        std::stringstream ss2(token);
        ss2 >> count >> color;
        if (color == "red")
            max_red = std::max(max_red, count);
        if (color == "green")
            max_green = std::max(max_green, count);
        if (color == "blue")
            max_blue = std::max(max_blue, count);
    }
    return {max_red, max_green, max_blue};
}

int get_powerset(const std::string &s)
{
    std::stringstream ss(s.substr(s.find(":") + 1));
    std::string record;
    max_struct mx = {};
    while (std::getline(ss, record, ';'))
    {
        max_struct m2 = get_powerset_record(record);
        mx.red = std::max(m2.red, mx.red);
        mx.green = std::max(m2.green, mx.green);
        mx.blue = std::max(m2.blue, mx.blue);
    }
    std::cout << mx.red << " " << mx.blue << " " << mx.green << ": " << mx.red * mx.blue *mx.green
              << std::endl;
    return mx.red * mx.blue * mx.green;
}

int main()
{
    std::ifstream input_file("input.txt");
    std::string line;
    int answer = 0;
    while (std::getline(input_file, line))
    {
        answer += get_powerset(line);
    }
    std::cout << "Answer: " << answer << std::endl;
}