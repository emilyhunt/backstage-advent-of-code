/**
 * @file 08.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 8
 * @version 1.0.0
 * @date 2021-12-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Declarations
================================================================================
*/

/*
================================================================================
                            Function Definitions
================================================================================
*/
std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>>
ParseSevenSegmentData(const std::string text)
{
    std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>>
        data;
    std::vector<std::string> left;
    std::vector<std::string> right;

    std::regex leftThenRightRegex("(.+)\\|(.+)");
    std::regex wordRegex("\\w+");
    std::smatch splitMatch, match;
    auto beginLines
        = std::sregex_iterator(text.begin(), text.end(), leftThenRightRegex);
    auto end = std::sregex_iterator();

    for (auto i = beginLines; i != end; i++)
    {
        splitMatch = *i;
        auto leftString = splitMatch[1].str();
        auto rightString = splitMatch[2].str();

        left.clear();
        right.clear();
        auto beginWords = std::sregex_iterator(leftString.begin(),
                                               leftString.end(), wordRegex);
        for (auto j = beginWords; j != end; j++)
        {
            match = *j;
            left.push_back(match[0]);
        }

        beginWords = std::sregex_iterator(rightString.begin(),
                                          rightString.end(), wordRegex);
        for (auto j = beginWords; j != end; j++)
        {
            match = *j;
            right.push_back(match[0]);
        }

        auto leftAndRight = std::make_pair(left, right);
        data.push_back(leftAndRight);
    }
    return data;
}

void PrintSevenSegmentData(
    const std::vector<
        std::pair<std::vector<std::string>, std::vector<std::string>>>& data)
{
    for (const auto& line : data)
    {
        for (const auto& word : line.first)
            std::cout << word << " ";

        std::cout << " | ";

        for (const auto& word : line.second)
            std::cout << word << " ";

        std::cout << "\n";
    }
}

int Part1(const std::vector<
          std::pair<std::vector<std::string>, std::vector<std::string>>>& data)
{
    size_t oneDigitLen = 2;
    size_t fourDigitLen = 4;
    size_t sevenDigitLen = 3;
    size_t eightDigitLen = 7;
    int sum = 0;

    for (const auto& line : data)
        for (const auto& word : line.second)
            if ((word.length() == oneDigitLen)
                || (word.length() == fourDigitLen)
                || (word.length() == sevenDigitLen)
                || (word.length() == eightDigitLen))
                sum++;
    return sum;
}

/**
 * @brief Day 8 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day8(const char* fileName)
{
    std::string text = ReadTextFile(fileName);
    std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>>
        data = ParseSevenSegmentData(text);
    std::cout << "Part 1: " << Part1(data) << "\n";
}
