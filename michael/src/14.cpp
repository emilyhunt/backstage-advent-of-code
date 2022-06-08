/**
 * @file 14.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 14
 * @version 1.0.0
 * @date 2021-12-14
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <unordered_map>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Create a map from the list in the file text
 *
 * @param text File text
 * @return std::unordered_map<std::string, std::string> Mapping pair of letters
 * to single letter
 */
std::unordered_map<std::string, std::string> CreateMap(const std::string& text)
{
    std::unordered_map<std::string, std::string> map;

    std::smatch match;
    std::regex regex("(\\w\\w) -> (\\w)");
    auto begin = std::sregex_iterator(text.begin(), text.end(), regex);
    auto end = std::sregex_iterator();
    for (auto i = begin; i != end; i++)
    {
        match = *i;
        map.insert(std::make_pair(match[1].str(), match[2].str()));
    }

    return map;
}

/**
 * @brief Solve part 1 and 2
 *
 * @param polymer The polymer string (i.e file input first line)
 * @param map Unordered map data structure for list in file
 * @param iterations Amount of iterations
 * @return int64_t Solution may be a large number for >10 iterations
 */
static int64_t Solve(std::string polymer,
                     const std::unordered_map<std::string, std::string>& map,
                     size_t iterations)
{
    std::unordered_map<std::string, int64_t> counts;
    std::set<char> letters;
    for (const auto& [left, right] : map)
        counts.insert(std::make_pair(left, 0));

    // Get initial count and letter set
    for (const auto& [key, val] : map)
    {
        letters.insert(val[0]);
        size_t pos = 0;
        while (polymer.find(key, pos) != std::string::npos)
        {
            pos = polymer.find(key, pos) + 1;
            counts[key]++;
        }
    }

    for (size_t i = 0; i < iterations; i++)
    {
        auto countsCopy = counts;
        for (const auto& [key, val] : map)
        {
            if (countsCopy[key] > 0)
            {
                counts[key[0] + val] += countsCopy[key];
                counts[val + key[1]] += countsCopy[key];
                counts[key] -= countsCopy[key];
            }
        }
    }

    const char firstLetter = polymer[0];
    const char lastLetter = polymer[polymer.length() - 1];

    std::unordered_map<char, uint64_t> letterCount(letters.size(),
                                                   letters.get_allocator());

    for (auto letter : letters)
    {
        uint64_t count = 0;
        for (const auto& [key, val] : counts)
        {
            count += std::count(key.begin(), key.end(), letter) * val;
        }
        count += (letter == firstLetter);
        count += (letter == lastLetter);
        letterCount[letter] = count / 2;
    }

    auto [smallest, largest] = std::minmax_element(
        letterCount.begin(), letterCount.end(),
        [](const std::pair<char, size_t>& p1, const std::pair<char, size_t>& p2)
        { return p1.second < p2.second; });

    return largest->second - smallest->second;
}

/**
 * @brief Day 14 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day14(const char* fileName)
{
    const std::string text = ReadTextFile(fileName);
    const std::unordered_map<std::string, std::string> map = CreateMap(text);
    const auto polymer = text.substr(0, text.find('\n'));

    std::cout << "Part 1: " << Solve(polymer, map, 10) << "\n";
    std::cout << "Part 2: " << Solve(polymer, map, 40) << "\n";
}
