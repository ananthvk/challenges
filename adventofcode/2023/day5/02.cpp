#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <stdint.h>
#include <vector>

// Pseudocode for mapping a source element to destination
// ranges[n] <- Read pairs of range {range_start, range_length, dest_start}
// SORT ranges in non-decreasing order
// function map(element)
//      lower = Greatest range less than or equal to element
//      IF element <= (lower.range_start + lower.range_length - 1)
//          mapped = lower.dest_start + (element - lower.range_start)
//      ELSE
//          mapped = element
//      return mapped

struct range
{
    long int start;
    long int length;
    long int destination_start;

    bool operator<(const range &other) const { return start < other.start; }
};

long int map_value(long int element, const std::set<range> &ranges)
{
    if (ranges.empty())
    {
        return element;
    }
    range closest;
    auto lb = ranges.lower_bound({element, 0, 0});
    if (lb == ranges.begin())
    {
        // No other element is smaller than this one
        return element;
    }
    else
    {
        if (lb != ranges.end() && lb->start == element)
        {
            closest = *lb;
        }
        else
        {
            closest = *(--lb);
        }
    }
    if (element <= (closest.start + closest.length - 1))
    {
        return closest.destination_start + (element - closest.start);
    }
    else
    {
        return element;
    }
}

void mapseeds(std::vector<long int> &seeds, std::set<range> &ranges)
{
    for (auto &seed : seeds)
    {
        seed = map_value(seed, ranges);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./a.out seed_start_field (0,2,4...)" << std::endl;
        exit(1);
    }
    std::ifstream ifs("input.txt");
    std::string seeds_line;
    std::getline(ifs, seeds_line);
    seeds_line = seeds_line.substr(seeds_line.find(' '));

    std::string line;
    bool new_category = false;

    std::stringstream sstream(seeds_line);

    std::vector<long int> seeds2;
    std::copy(std::istream_iterator<long int>(sstream), std::istream_iterator<long int>(),
              std::back_inserter(seeds2));

    std::vector<long int> seeds;
    // Bruteforce
    // for (int i = 0; i < seeds2.size() - 1; i += 2)
    // {
    int i = std::stoi(argv[1]);
    for (int j = 0; j < seeds2[i + 1]; j++)
    {
        seeds.push_back(seeds2[i] + j);
    }
    std::cerr << "Processed " << i + 1 << " seed" << std::endl;
    // }
    std::cerr << "Total seeds:" << seeds.size() << std::endl;

    // std::copy(seeds.begin(), seeds.end(), std::ostream_iterator<long int>(std::cout, " "));
    // std::cout << std::endl;

    std::set<range> ranges;

    while (std::getline(ifs, line))
    {
        if (line.empty())
        {
            // The next line is a mapping string, ignore it
            new_category = true;
            continue;
        }
        if (new_category)
        {
            std::cerr << "To process " << line << std::endl;
            new_category = false;
            mapseeds(seeds, ranges);
            ranges.clear();
            continue;
        }
        // Map from one category to the next
        std::stringstream ss(line);
        long int dest, src, length;
        ss >> dest >> src >> length;
        ranges.insert({src, length, dest});
    }
    mapseeds(seeds, ranges);
    std::cout << *std::min_element(seeds.begin(), seeds.end()) << std::endl;
}