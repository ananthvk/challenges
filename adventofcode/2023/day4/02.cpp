#include <algorithm>
#include <fstream>
#include<numeric>
#include <iostream>
#include <iterator>
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
    int prefix_table[250] = {0};
    int csum = 1;
    while (std::getline(ifs, line))
    {
        std::set<int> s;
        int winning_cards = 0;
        int card_id =
            std::stoi(line.substr(line.find(" ") + 1, line.find(":") - line.find(" ") - 1));
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
        // We get 'winning_card' number of cards after this card
        // Construct a prefix table
        // csum is the number of cards with card_id
        csum += prefix_table[card_id];
        prefix_table[card_id + 1] += csum;
        prefix_table[card_id + 1 + winning_cards] -= csum;
        std::cout << card_id<< ": " << csum << std::endl;
        answer += csum;
    }
    std::cout << std::endl << "Answer: " << answer << std::endl;
}