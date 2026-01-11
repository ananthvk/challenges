#include <fstream>
#include <iostream>
#include <sstream>

// Checks if a single record i.e. until the ; is valid or not
bool is_record_valid(const std::string &record)
{
    std::stringstream ss(record);
    std::string token;
    while (std::getline(ss, token, ','))
    {
        std::string color;
        int count;
        std::stringstream ss2(token);
        ss2 >> count >> color;
        if (color == "red" && count > 12)
            return false;
        if (color == "green" && count > 13)
            return false;
        if (color == "blue" && count > 14)
            return false;
    }

    return true;
}

// Parses a single input line, returns game ID if the game is possible
// otherwise return -1
int get_valid_game_id(const std::string &s)
{
    int game_id = std::stoi(s.substr(s.find(" ") + 1, s.find(":") - s.find(" ") - 1));
    std::stringstream ss(s.substr(s.find(":") + 1));
    std::string record;
    while (std::getline(ss, record, ';'))
    {
        if (!is_record_valid(record))
            return -1;
    }
    return game_id;
}

int main()
{
    std::ifstream input_file("input.txt");
    std::string line;
    int answer = 0;
    while (std::getline(input_file, line))
    {
        int k = get_valid_game_id(line);
        if (k != -1)
            answer += k;
    }
    std::cout << "Answer: " << answer << std::endl;
}