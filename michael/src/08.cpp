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
#include <chrono>
#include <iostream>
#include <iterator>
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
                            Function Declarations
================================================================================
*/

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
    std::pair<std::array<std::set<char>, 10>, std::array<std::set<char>, 4>>>
ParseSevenSegmentData(const std::string& text)
{
    std::vector<std::pair<std::array<std::set<char>, 10>,
                          std::array<std::set<char>, 4>>>
        data;

    std::stringstream textStream(text);
    std::string line;
    const size_t pipeLocation = text.find("|");

    while (std::getline(textStream, line))
    {
        std::stringstream left(line.substr(0, pipeLocation - 1));
        std::stringstream right(line.substr(pipeLocation + 2));

        std::array<std::set<char>, 10> leftvector;
        std::array<std::set<char>, 4> rightvector;

        std::string word;

        size_t i = 0;
        while (left >> word)
            leftvector[i++] = std::set<char>(word.begin(), word.end());

        i = 0;
        while (right >> word)
            rightvector[i++] = std::set<char>(word.begin(), word.end());

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
                                std::array<std::set<char>, 4>>>& data)
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
static int
Part1(const std::vector<std::pair<std::array<std::set<char>, 10>,
                                  std::array<std::set<char>, 4>>>& data)
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
 * @brief Check if the character is in the string
 *
 * @param ch Character to check for
 * @param str String to check in
 * @return true Character was found in string
 * @return false Character was not found in string
 */
bool CheckCharInStr(char ch, const std::string& str)
{
    for (auto i = str.begin(); i != str.end(); i++)
        if (ch == *i)
            return true;

    return false;
}

/**
 * @brief Check if the whole of the A string is in B
 *
 * @param a String to check for
 * @param b String to check in
 * @return true All of A is in B
 * @return false Not all of A is in B
 */
bool CheckAllAInB(const std::string& a, const std::string& b)
{
    for (auto i = a.begin(); i != a.end(); i++)
        if (!CheckCharInStr(*i, b))
            return false;

    return true;
}

/**
 * @brief Solve part 2
 *
 * @param data Data extracted from text file
 * @return int Solution to part 2
 */
static int
Part2(const std::vector<std::pair<std::array<std::set<char>, 10>,
                                  std::array<std::set<char>, 4>>>& data)
{
    int sum = 0;

    std::vector<std::unordered_map<std::string, int>> digitMappings;
    std::stringstream ss;

    for (const auto& line : data)
    {
        std::unordered_map<int, std::set<char>> digitMapping;
        std::vector<std::set<char>> digitsToFind;
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
            else
                digitsToFind.push_back(word);
        }

        for (const auto& digit : digitsToFind)
        {
            std::set<char> intersectOne;
            std::set<char> intersectFour;
            std::set_intersection(
                digitMapping[1].begin(), digitMapping[1].end(), digit.begin(),
                digit.end(), std::inserter(intersectOne, intersectOne.begin()));
            std::set_intersection(
                digitMapping[4].begin(), digitMapping[4].end(), digit.begin(),
                digit.end(),
                std::inserter(intersectFour, intersectFour.begin()));
            if ((intersectOne == digitMapping[1])
                && (intersectFour == digitMapping[4]))
            {
                digitMapping[9] = digit;
                break;
            }
        }

        for (const auto& digit : digitsToFind)
        {
            std::set<char> intersectOne;
            std::set<char> intersectFour;
            std::set_intersection(
                digitMapping[1].begin(), digitMapping[1].end(), digit.begin(),
                digit.end(), std::inserter(intersectOne, intersectOne.begin()));
            std::set_intersection(
                digitMapping[4].begin(), digitMapping[4].end(), digit.begin(),
                digit.end(),
                std::inserter(intersectFour, intersectFour.begin()));
            if ((intersectOne == digitMapping[1])
                && (intersectFour != digitMapping[4]))
            {
                if (digit.size() == 5)
                    digitMapping[3] = digit;
                else
                    digitMapping[0] = digit;
            }
        }

        for (const auto& [key, val]:digitMapping){
            std::cout << key<<": ";
            for (const auto& elem:val)
            {
                std::cout<<elem;
            }
            std::cout << ", ";
        }
        std::cout << "\n";

        // // 0, 2, 3, 5, 6
        // // Use overlap of 1 with 0 and 6 to solve those
        // for (const auto& digit : zeroSixAndNineDigits)
        // {
        //     std::set<char> intersection;
        //     std::set_intersection(digitMapping[1].begin(),
        //                           digitMapping[1].end(), digit.begin(),
        //                           digit.end(), intersection.begin());
        //     if (intersection == digitMapping[1])
        //     {
        //         digitMapping[0] = digit;
        //     }
        //     else
        //     {
        //         digitMapping[6] = digit;
        //     }
        // }

        // // 2, 3, 5
        // // Use overlap of 1 with 2, 3 and 5 to find 3
        // for (const auto& digit : twoThreeAndFiveDigits)
        // {
        //     std::set<char> intersection;
        //     std::set_intersection(digitMapping[1].begin(),
        //                           digitMapping[1].end(), digit.begin(),
        //                           digit.end(), intersection.begin());
        //     if (intersection == digitMapping[1])
        //     {
        //         digitMapping[3] = digit;
        //         break;
        //     }
        // }
        // twoThreeAndFiveDigits.remove(digitMapping[3]);

        // // 2, 5
        // // Use overlap of 9 with 2 and 5 to find 5
        // for (const auto& digit : twoThreeAndFiveDigits)
        // {
        //     std::set<char> intersection;
        //     std::set_intersection(digitMapping[9].begin(),
        //                           digitMapping[9].end(), digit.begin(),
        //                           digit.end(), intersection.begin());
        //     if (intersection == digitMapping[9])
        //     {
        //         digitMapping[5] = digit;
        //     }
        //     else
        //     {
        //         digitMapping[2] = digit;
        //     }
        // }

        // for (const auto& digit : line.second)
        // {
        //     auto [key, val] = *std::find(digitMapping.begin(),
        //     digitMapping.end(), digit); ss << key;
        // }
        // int val;
        // ss >> val;
        // sum += val;
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
    auto t1 = std::chrono::high_resolution_clock::now();
    std::string text = ReadTextFile(fileName);
    auto data = ParseSevenSegmentData(text);
    // PrintSevenSegmentData(data);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1: " << Part1(data) << "\n";
    auto t3 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2: \n" << Part2(data) << "\n";
    auto t4 = std::chrono::high_resolution_clock::now();

    auto readFileTime
        = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1)
              .count();
    auto solvePart1Time
        = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2)
              .count();
    auto solvePart2Time
        = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3)
              .count();

    std::cout << "File read and parsed in: " << readFileTime << "us\n";
    std::cout << "Part 1 completed in: " << solvePart1Time << "us\n";
    std::cout << "Part 2 completed in: " << solvePart2Time << "us\n";
}
