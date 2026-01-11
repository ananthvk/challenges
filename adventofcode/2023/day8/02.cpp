#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <set>

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

void insert_if_last_char_equals(std::set<std::string> &s, std::string st, char last)
{
    // The nodes are only 3 letters long
    if (st[2] == last)
    {
        s.insert(st);
    }
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
    std::set<std::string> nodes;
    std::set<std::string> Aset;
    std::set<std::string> Zset;

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

        for (int i = 1; i <= 3; i++)
        {
            nodes.insert(result[i]);
            insert_if_last_char_equals(Aset, result[i], 'A');
            insert_if_last_char_equals(Zset, result[i], 'Z');
        }
    }

    // Find the solution
    int moves = 0;
    while (Aset != Zset)
    {
        std::set<std::string> temp;
        char seq = get_nextmove(sequence);
        for (const auto &elem : Aset)
        {
            if (seq == 'R')
            {
                temp.insert(network[elem].right);
            }
            else
            {
                temp.insert(network[elem].left);
            }
        }
        Aset = temp;
        moves++;
    }
    std::cout << "Number of moves: " << moves << std::endl;
}