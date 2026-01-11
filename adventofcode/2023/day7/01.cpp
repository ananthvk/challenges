#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>

// 0 ->
// 1 ->
// 2 -> 2
// 3 -> 3
// 4 -> 4
// ...
// T -> 10
// J -> 11
// Q -> 12
// K -> 13
// A -> 14


class Hand
{
    std::string cards;
    unsigned long long int bid_;
    // If repetitions[1] = 2, it means that there are 2 unique cards
    uint8_t repetitions[6];

    int char_to_rank(int ch) const
    {
        if (isdigit(ch))
            return ch - '0';
        else
        {
            int v = 0;
            switch (ch)
            {
            case 'T':
                v = 10;
                break;
            case 'J':
                v = 11;
                break;
            case 'Q':
                v = 12;
                break;
            case 'K':
                v = 13;
                break;
            case 'A':
                v = 14;
                break;
            default:
                std::cout << "Invalid literal" << std::endl;
                exit(1);
            }
            return v;
        }
    }

  public:
    Hand(const std::string &cards, unsigned long long int bid)
        : cards(cards), bid_(bid), repetitions()
    {
        uint8_t table[15] = {0};
        for (const auto &c : cards)
        {
            table[char_to_rank(c)]++;
        }
        for (const auto &e : table)
        {
            if (e)
                repetitions[e]++;
        }
        // std::cout << cards << " ";
        // std::copy(std::begin(repetitions), std::end(repetitions),
        //           std::ostream_iterator<unsigned long long int>(std::cout, " "));
        // std::cout << std::endl;
    }

    unsigned long long int bid() { return bid_; }

    bool operator<(const Hand &other) const
    {
        for (int i = 5; i > 0; i--)
        {
            if (other.repetitions[i] > repetitions[i])
                return true;
            else if (other.repetitions[i] < repetitions[i])
                return false;
        }
        for (int i = 0; i < 5; i++)
        {
            if (char_to_rank(other.cards[i]) > char_to_rank(cards[i]))
            {
                return true;
            }
            else if (char_to_rank(other.cards[i]) < char_to_rank(cards[i]))
                return false;
        }
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Hand &h);
};

std::ostream &operator<<(std::ostream &os, const Hand &h) { return os << h.cards; }

int main()
{
    /*
    Hand h("32T3K", 765);
    Hand j("T55J5", 684);
    Hand k("KK677", 28);
    Hand l("KTJJT", 220);
    Hand m("QQQJA", 483);
    std::vector<Hand> hands = {j, k};
    std::cout << "0: " << (hands[1] < hands[1]) << std::endl;
    std::cout << "0: " << (hands[0] < hands[0]) << std::endl;
    std::cout << "1: " << (hands[1] < hands[0]) << std::endl;
    std::cout << "0: " << (hands[0] < hands[1]) << std::endl;
    */
    std::vector<Hand> hands;

    std::ifstream ifs("input.txt");
    std::string line;
    std::string hand;
    int bid;
    while (std::getline(ifs, line))
    {
        std::stringstream ss(line);
        ss >> hand >> bid;
        hands.push_back(Hand(hand, bid));
    }

    std::sort(hands.begin(), hands.end());
    unsigned long long int sum = 0;
    // std::cout << "==========================" << std::endl;
    for (int i = 0; i < hands.size(); i++)
    {
        sum += (i + 1) * (hands[i].bid());
        // std::cout << hands[i] << std::endl;
    }
    std::cout << "Answer: " << sum << std::endl;
}