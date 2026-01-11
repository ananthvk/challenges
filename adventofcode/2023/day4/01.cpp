#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

enum State
{
    WINNING_CARD_LIST,
    OWNED_CARD_LIST
};

int power(int base, int e)
{
    int answer = 1;
    for (int i = 1; i <= e; i++)
        answer *= base;
    return answer;
}

int main()
{
    std::ifstream ifs("input.txt");
    int answer = 0;
    std::string line;
    while (std::getline(ifs, line))
    {
        std::set<int> s;
        int winning_cards = 0;
        std::stringstream ss(line.substr(line.find(":") + 1));
        std::string token;
        State current_state = WINNING_CARD_LIST;

        while (std::getline(ss, token, ' '))
        {
            if (!token.size())
                continue;
            if (token == "|")
            {
                current_state = OWNED_CARD_LIST;
                continue;
            }
            if (current_state == WINNING_CARD_LIST)
            {
                s.insert(std::stoi(token));
            }
            if (current_state == OWNED_CARD_LIST && s.find(std::stoi(token)) != s.end())
            {
                winning_cards += 1;
            }
        }
        if (winning_cards <= 1)
        {
            std::cout << winning_cards << ", ";
            answer += winning_cards;
        }
        else
        {
            std::cout << power(2, winning_cards - 1) << ", ";
            answer += power(2, winning_cards - 1);
        }
    }
    std::cout <<std::endl<< "Answer: " << answer << std::endl;
}