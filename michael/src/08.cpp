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
#include <chrono>
#include <iostream>
#include <list>
#include <regex>
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
            std::string word = match[0];
            std::sort(word.begin(), word.end());
            left.push_back(word);
        }

        beginWords = std::sregex_iterator(rightString.begin(),
                                          rightString.end(), wordRegex);
        for (auto j = beginWords; j != end; j++)
        {
            match = *j;
            std::string word = match[0];
            std::sort(word.begin(), word.end());
            right.push_back(word);
        }

        auto leftAndRight = std::make_pair(left, right);
        data.push_back(leftAndRight);
    }
    return data;
}

/**
 * @brief Print the seven segment data for debugging
 *
 * @param data data to be printed
 */
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
Part1(const std::vector<
      std::pair<std::vector<std::string>, std::vector<std::string>>>& data)
{
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
Part2(const std::vector<
      std::pair<std::vector<std::string>, std::vector<std::string>>>& data)
{
    int sum = 0;

    std::vector<std::unordered_map<std::string, int>> digitMappings;

    for (const auto& line : data)
    {
        std::unordered_map<std::string, int> digitMapping;
        std::vector<std::string> uniques;
        std::vector<std::string> nonUniques;
        for (const auto& word : line.first)
        {
            if ((word.length() == oneDigitLen)
                || (word.length() == fourDigitLen)
                || (word.length() == sevenDigitLen)
                || (word.length() == eightDigitLen))
                uniques.push_back(word);
            else
                nonUniques.push_back(word);
        }

        std::sort(uniques.begin(), uniques.end(),
                  [](std::string a, std::string b)
                  { return a.length() < b.length(); });

        std::sort(nonUniques.begin(), nonUniques.end(),
                  [](std::string a, std::string b)
                  { return a.length() < b.length(); });

        std::list<std::string> twoThreeAndFiveDigits(nonUniques.begin(),
                                                     nonUniques.begin() + 3);
        std::list<std::string> zeroSixAndNineDigits(nonUniques.begin() + 3,
                                                    nonUniques.end());

        // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        const std::string oneDigit = uniques[0];
        const std::string sevenDigit = uniques[1];
        const std::string fourDigit = uniques[2];
        const std::string eightDigit = uniques[3];

        // 0, 2, 3, 5, 6, 9
        // Use overlap of 4 with (0, 6, 9) to find 9
        std::string nineDigit;
        for (const std::string& digit : zeroSixAndNineDigits)
            if (CheckAllAInB(fourDigit, digit))
                nineDigit = digit;

        // 0, 2, 3, 5, 6
        // Use overlap of 1 with 0 and 6 to solve those
        std::string zeroDigit;
        zeroSixAndNineDigits.remove(nineDigit);
        for (const std::string& digit : zeroSixAndNineDigits)
            if (CheckAllAInB(oneDigit, digit))
                zeroDigit = digit;
        zeroSixAndNineDigits.remove(zeroDigit);
        const std::string sixDigit = zeroSixAndNineDigits.front();

        // 2, 3, 5
        // Use overlap of 1 with 2, 3 and 5 to find 3
        std::string threeDigit;
        for (const std::string& digit : twoThreeAndFiveDigits)
            if (CheckAllAInB(oneDigit, digit))
                threeDigit = digit;

        // 2, 5
        // Use overlap of 9 with 2 and 5 to find 5
        std::string fiveDigit;
        twoThreeAndFiveDigits.remove(threeDigit);
        for (const std::string& digit : twoThreeAndFiveDigits)
            if (CheckAllAInB(digit, nineDigit))
                fiveDigit = digit;
        twoThreeAndFiveDigits.remove(fiveDigit);
        const std::string twoDigit = twoThreeAndFiveDigits.front();

        digitMapping.insert(std::make_pair(zeroDigit, 0));
        digitMapping.insert(std::make_pair(oneDigit, 1));
        digitMapping.insert(std::make_pair(twoDigit, 2));
        digitMapping.insert(std::make_pair(threeDigit, 3));
        digitMapping.insert(std::make_pair(fourDigit, 4));
        digitMapping.insert(std::make_pair(fiveDigit, 5));
        digitMapping.insert(std::make_pair(sixDigit, 6));
        digitMapping.insert(std::make_pair(sevenDigit, 7));
        digitMapping.insert(std::make_pair(eightDigit, 8));
        digitMapping.insert(std::make_pair(nineDigit, 9));

        digitMappings.push_back(digitMapping);

        std::stringstream ss;
        for (const auto& key : line.second)
            ss << digitMapping[key];
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
    auto t0 = std::chrono::high_resolution_clock::now();
    std::string text = ReadTextFile(fileName);
    // auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>>
        data = ParseSevenSegmentData(text);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 1: " << Part1(data) << "\n";
    auto t3 = std::chrono::high_resolution_clock::now();
    std::cout << "Part 2: " << Part2(data) << "\n";
    auto t4 = std::chrono::high_resolution_clock::now();

    auto readFileTime
        = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t0)
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
