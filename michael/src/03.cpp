/**
 * @file 03.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 3
 * @version 1.0.0
 * @date 2021-12-04
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <tuple>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Classes etc.
================================================================================
*/

/**
 * @brief Rate option
 */
enum class Rate
{
    Epsilon,
    Gamma
};

/**
 * @brief Rating option
 */
enum class Rating
{
    OxygenGenerator,
    Co2Scrubber
};

/*
================================================================================
                            Function Declarations
================================================================================
*/
int Part1(const std::vector<std::string>& lines);
int Part2(const std::vector<std::string>& lines);
std::vector<std::string> ExtractLines(const std::string& text);
int BinaryToDecimal(const std::vector<unsigned int>& binaryVector);
int CalculateRate(const std::vector<std::string>& lines, Rate option);
int CalculateRating(const std::vector<std::string>& lines, Rating option);
std::vector<unsigned int> CountBits(const std::vector<std::string>& lines);

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Solve part 1
 *
 * @param lines Puzzle input
 * @return int Solution
 */
int Part1(const std::vector<std::string>& lines)
{
    return CalculateRate(lines, Rate::Gamma)
           * CalculateRate(lines, Rate::Epsilon);
}

/**
 * @brief Solve part 2
 *
 * @param lines Puzzle input
 * @return int Solution
 */
int Part2(const std::vector<std::string>& lines)
{
    return CalculateRating(lines, Rating::OxygenGenerator)
           * CalculateRating(lines, Rating::Co2Scrubber);
}

/**
 * @brief Convert text file to vector of strings seperated with whitespace
 *
 * @param text Text from file
 * @return std::vector<std::string> Split string into vector of strings on
 * whitespace
 */
std::vector<std::string> ExtractLines(const std::string& text)
{
    std::stringstream textStream(text);
    std::vector<std::string> lines;
    std::string tempString;

    while (textStream >> tempString)
        lines.push_back(tempString);

    return lines;
}

/**
 * @brief Convert binary vector to decimal
 *
 * @param binaryVector vector of 1s and 0s
 * @return int Decimal number after conversion
 */
int BinaryToDecimal(const std::vector<unsigned int>& binaryVector)
{
    int decimalValue = 0;
    int j = 0;
    for (auto i = binaryVector.rbegin(); i != binaryVector.rend(); i++)
    {
        decimalValue += (*i << j);
        j++;
    }
    return decimalValue;
}

/**
 * @brief Convert binary string to decimal
 *
 * @param binaryString binary string such as "0010111011"
 * @return int Decimal number after conversion
 */
int BinaryToDecimal(const std::string& binaryString)
{
    int decimalValue = 0;
    int j = 0;
    for (auto i = binaryString.rbegin(); i != binaryString.rend(); i++)
    {
        decimalValue += ((*i != '0') << j);
        j++;
    }
    return decimalValue;
}

/**
 * @brief Calculate the Rate::Gamma or Rate::Epsilon rate
 *
 * @param lines Vector of string lines
 * @param option the Rate option
 * @return int Calculated rate
 */
int CalculateRate(const std::vector<std::string>& lines, Rate option)
{
    const int width = lines[0].length();
    auto gammaRate = CountBits(lines);

    for (int i = 0; i < width; i++)
    {
        if (gammaRate[i] > (lines.size() / 2))
            gammaRate[i] = 1;
        else
            gammaRate[i] = 0;
    }

    int decimalGammaRate = BinaryToDecimal(gammaRate);

    switch (option)
    {
    case Rate::Gamma:
        return decimalGammaRate;

    case Rate::Epsilon:
        return (~decimalGammaRate) & ((1 << gammaRate.size()) - 1);

    default:
        std::cerr << "Option '" << static_cast<int>(option)
                  << "' is not allowed\n";
        return 0;
    }
}

/**
 * @brief Calculate the Rating::OxygenGenerator or Rating::Co2Scrubber rating
 *
 * @param lines Vector of string lines
 * @param option the Rating option
 * @return int Calculated rating
 */
int CalculateRating(const std::vector<std::string>& lines, Rating option)
{
    unsigned int i = 0;
    std::list<std::string> linesList(lines.begin(), lines.end());

    while ((linesList.size() > 1) && (i < lines[0].length()))
    {
        std::vector<std::string> linesReduced(linesList.begin(),
                                              linesList.end());
        auto bitCount = CountBits(linesReduced);
        char charSelected = '0';

        if (bitCount[i]
            >= ((linesReduced.size() / 2) + (linesReduced.size() % 2)))
            charSelected = '1';

        switch (option)
        {
        case Rating::OxygenGenerator:
            linesList.remove_if([=](auto s) { return s[i] != charSelected; });
            break;

        case Rating::Co2Scrubber:
            linesList.remove_if([=](auto s) { return s[i] == charSelected; });
            break;

        default:
            std::cerr << "Option '" << static_cast<int>(option)
                      << "' is not allowed\n";
            return 0;
        }
        i++;
    }

    std::string binaryNum;
    for (auto line : linesList)
        binaryNum = line;

    return BinaryToDecimal(binaryNum);
}

/**
 * @brief Count number of 1s at each position of the binary numbers in the list
 *
 * @param lines Vector of binary strings
 * @return std::vector<unsigned int> Count of 1s at each bit
 */
std::vector<unsigned int> CountBits(const std::vector<std::string>& lines)
{
    int width = lines[0].length();
    std::vector<unsigned int> bitCount(width, 0);
    for (auto line : lines)
        for (int i = 0; i < width; i++)
            if (line[i] == '1')
                bitCount[i]++;

    return bitCount;
}

/**
 * @brief Start of program execution
 *
 * @return int return 0 for normal running
 */
void Day3()
{
    std::string text = ReadTextFile("03/data/input.txt");
    auto lines = ExtractLines(text);

    std::cout << "Part 1: " << Part1(lines) << "\n";
    std::cout << "Part 2: " << Part2(lines) << "\n";
}
