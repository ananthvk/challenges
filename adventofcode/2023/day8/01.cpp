#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>

struct MapEntry
{
    std::string left;
    std::string right;
};

char get_nextmove(const std::string &s)
{
    // Note s.size() must not be zero
    static int i = 0;
    return s[(i++) % s.size()];
}

int main()
{
    std::string sequence;
    std::string line;
    std::ifstream ifs("input.txt");

    // Get the sequence of RLRL....
    std::getline(ifs, sequence);

    // Ignore the blank line
    std::getline(ifs, line);

    std::map<std::string, MapEntry> network;

    // Get the lines
    while (std::getline(ifs, line))
    {
        std::regex instructions_regex{R"((\w+)\s*=\s*\((\w+),\s*(\w+)\))"};
        std::smatch result;
        if (!std::regex_search(line, result, instructions_regex))
        {
            std::cerr << "Syntax error on line: " << line << std::endl;
            return 1;
        }
        network[result[1]] = MapEntry{result[2], result[3]};
    }

    // Find the solution
    int moves = 0;
    std::string current = "AAA";
    while (current != "ZZZ")
    {
        if (get_nextmove(sequence) == 'R')
        {
            current = network[current].right;
        }
        else
        {
            current = network[current].left;
        }
        moves++;
    }
    std::cout << "Number of moves: " << moves << std::endl;
}