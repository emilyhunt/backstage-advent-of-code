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

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Parse seven segment data from file to data structure
 *
 * @param text from input data file
 * @return std::vector<std::pair<std::vector<std::string>,
 * std::vector<std::string>>> file contents in data structure
 */
std::vector<
    std::pair<std::array<std::set<char>, 10>, std::array<std::string, 4>>>
ParseSevenSegmentData(const std::string& text)
{
    std::vector<
        std::pair<std::array<std::set<char>, 10>, std::array<std::string, 4>>>
        data;

    std::stringstream textStream(text);
    std::string line;
    const size_t pipeLocation = text.find("|");

    while (std::getline(textStream, line))
    {
        std::stringstream left(line.substr(0, pipeLocation - 1));
        std::stringstream right(line.substr(pipeLocation + 2));

        std::array<std::set<char>, 10> leftvector;
        std::array<std::string, 4> rightvector;

        std::string word;

        size_t i = 0;
        while (left >> word)
            leftvector[i++] = std::set<char>(word.begin(), word.end());

        i = 0;
        while (right >> word)
        {
            std::sort(word.begin(), word.end());
            rightvector[i++] = word;
        }
        data.push_back(std::make_pair(leftvector, rightvector));
    }
    return data;
}

/**
 * @brief Print the seven segment data for debugging
 *
 * @param data data to be printed
 */
void PrintSevenSegmentData(
    const std::vector<std::pair<std::array<std::set<char>, 10>,
                                std::array<std::string, 4>>>& data)
{
    for (const auto& line : data)
    {
        for (const auto& word : line.first)
        {
            std::copy(word.begin(), word.end(),
                      std::ostreambuf_iterator<char>(std::cout));
            std::cout << " ";
        }

        std::cout << "| ";

        for (const auto& word : line.second)
        {
            std::copy(word.begin(), word.end(),
                      std::ostreambuf_iterator<char>(std::cout));
            std::cout << " ";
        }

        std::cout << "\n";
    }
}

static const size_t oneDigitLen = 2;   ///< Amount of segments for one digit
static const size_t fourDigitLen = 4;  ///< Amount of segments for four digit
static const size_t sevenDigitLen = 3; ///< Amount of segments for seven digit
static const size_t eightDigitLen = 7; ///< Amount of segments for eight digit

/**
 * @brief Solve part 1
 *
 * @param data Data extracted from text file
 * @return int Solution to part 1
 */
static int Part1(const std::vector<std::pair<std::array<std::set<char>, 10>,
                                             std::array<std::string, 4>>>& data)
{
    int sum = 0;

    for (const auto& line : data)
        for (const auto& word : line.second)
            if ((word.size() == oneDigitLen) || (word.size() == fourDigitLen)
                || (word.size() == sevenDigitLen)
                || (word.size() == eightDigitLen))
                sum++;
    return sum;
}

/**
 * @brief Solve part 2
 *
 * @param data Data extracted from text file
 * @return int Solution to part 2
 */
static int Part2(const std::vector<std::pair<std::array<std::set<char>, 10>,
                                             std::array<std::string, 4>>>& data)
{
    int sum = 0;

    std::vector<std::unordered_map<std::string, int>> digitMappings;

    for (const auto& line : data)
    {
        std::unordered_map<int, std::set<char>> digitMapping;
        std::list<std::set<char>> twoThreeFive;
        std::list<std::set<char>> zeroSixNine;

        for (const auto& word : line.first)
        {
            if (word.size() == oneDigitLen)
                digitMapping[1] = word;
            else if (word.size() == fourDigitLen)
                digitMapping[4] = word;
            else if (word.size() == sevenDigitLen)
                digitMapping[7] = word;
            else if (word.size() == eightDigitLen)
                digitMapping[8] = word;
            else if (word.size() == 5)
                twoThreeFive.push_back(word);
            else if (word.size() == 6)
                zeroSixNine.push_back(word);
            else
                throw std::logic_error("Unknown digit found");
        }

        for (const auto& digit : twoThreeFive)
        {
            std::set<char> intersect;
            std::set_intersection(
                digitMapping[1].begin(), digitMapping[1].end(), digit.begin(),
                digit.end(), std::inserter(intersect, intersect.begin()));
            if (intersect == digitMapping[1])
            {
                digitMapping[3] = digit;
                twoThreeFive.remove(digit);
                break;
            }
        }

        for (const auto& digit : twoThreeFive)
        {
            std::set<char> intersect;
            std::set_intersection(
                digitMapping[4].begin(), digitMapping[4].end(), digit.begin(),
                digit.end(), std::inserter(intersect, intersect.begin()));
            if (intersect.size() == 3)
            {
                digitMapping[5] = digit;
                twoThreeFive.remove(digit);
                break;
            }
        }
        digitMapping[2] = twoThreeFive.front();

        for (const auto& digit : zeroSixNine)
        {
            std::set<char> intersect;
            std::set_intersection(
                digitMapping[4].begin(), digitMapping[4].end(), digit.begin(),
                digit.end(), std::inserter(intersect, intersect.begin()));
            if (intersect == digitMapping[4])
            {
                digitMapping[9] = digit;
                zeroSixNine.remove(digit);
                break;
            }
        }

        for (const auto& digit : zeroSixNine)
        {
            std::set<char> intersect;
            std::set_intersection(
                digitMapping[1].begin(), digitMapping[1].end(), digit.begin(),
                digit.end(), std::inserter(intersect, intersect.begin()));
            if (intersect == digitMapping[1])
            {
                digitMapping[0] = digit;
                zeroSixNine.remove(digit);
                break;
            }
        }
        digitMapping[6] = zeroSixNine.front();

        std::map<std::string, int> reverseDigitMapping;
        for (const auto& [key, val] : digitMapping)
        {
            std::string s;
            for (const auto& ch : val)
                s.push_back(ch);
            std::sort(s.begin(), s.end());
            reverseDigitMapping[s] = key;
        }

        std::stringstream ss;
        for (const auto& digit : line.second)
        {
            ss << reverseDigitMapping[digit];
        }
        int val;
        ss >> val;
        sum += val;
    }

    return sum;
}

/**
 * @brief Day 8 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day08(const char* fileName)
{
    std::string text = ReadTextFile(fileName);
    auto data = ParseSevenSegmentData(text);
    std::cout << "Part 1: " << Part1(data) << "\n";
    std::cout << "Part 2: " << Part2(data) << "\n";
}
