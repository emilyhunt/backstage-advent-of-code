/**
 * @file 17.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 17
 * @version 1.0.0
 * @date 2021-12-17
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <array>
#include <cmath>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <utility>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Solve both parts, returned as a pair
 *
 * @param bounds of the finish rectangle
 * @return std::pair<int, int> Answer to part 1 followed by part 2
 */
static std::pair<int, int> Part1And2(
    const std::pair<std::pair<int, int>, const std::pair<int, int>>& bounds)
{
    const auto& [x, y] = bounds;

    const int minXv = std::sqrt(std::abs(2 * x.first)) * Sign(x.first);
    const int maxXv = x.second;
    const int minYv = y.first;
    const int maxYv = -y.first + 1;

    const auto start = std::make_pair(0, 0);

    int highestY = 0;

    std::set<std::pair<int, int>> success;

    for (int i = minXv; i <= maxXv; i++)
    {
        for (int j = minYv; j <= maxYv; j++)
        {
            auto currentVel = std::make_pair(i, j);
            auto currentPos = start;
            int localHighest = 0;

            while ((currentPos.first <= x.second)
                   && (currentPos.second >= y.first))
            {
                currentPos.first += currentVel.first;
                currentPos.second += currentVel.second;

                localHighest = std::max(localHighest, currentPos.second);

                if ((currentPos.first >= x.first)
                    && (currentPos.first <= x.second)
                    && (currentPos.second >= y.first)
                    && (currentPos.second <= y.second))
                {
                    success.insert(std::make_pair(i, j));
                    highestY = std::max(highestY, localHighest);
                    break;
                }

                if (x.first > 0)
                    currentVel.first = std::max(currentVel.first - 1, 0);
                else
                    currentVel.first = std::min(currentVel.first + 1, 0);

                currentVel.second--;
            }
        }
    }

    return std::make_pair(highestY, success.size());
}

/**
 * @brief Get the finishing area bounds from the input file
 *
 * @param text File contents
 * @return std::pair<std::pair<int, int>, std::pair<int, int>> pair of int pairs
 */
static std::pair<std::pair<int, int>, std::pair<int, int>>
GetBounds(const std::string& text)
{
    auto regex = std::regex("x=(-*\\d+)..(-*\\d+), y=(-*\\d+)..(-*\\d+)");
    std::cmatch match;

    std::array<int, 4> bounds = {};

    if (std::regex_search(text.c_str(), match, regex))
        for (size_t i = 0; i < bounds.size(); i++)
            bounds[i] = std::stoi(match[i + 1].str());

    return std::make_pair(std::make_pair(bounds[0], bounds[1]),
                          std::make_pair(bounds[2], bounds[3]));
}

/**
 * @brief Day 17 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day17(const char* fileName)
{
    const std::string text = ReadTextFile(fileName);
    auto bounds = GetBounds(text);
    auto [part1, part2] = Part1And2(bounds);
    std::cout << "Part 1: " << part1 << "\n"
              << "Part 2: " << part2 << "\n";
}
