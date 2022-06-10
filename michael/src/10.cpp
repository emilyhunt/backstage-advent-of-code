/**
 * @file 10.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 10
 * @version 1.0.0
 * @date 2021-12-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
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
 * @brief Replace all occurrences of 'what' with 'with' in the 'inOutStr'
 *
 * @param inOutStr Reference to string to be modifed with replacements
 * @param what Search for this and replace with 'with'
 * @param with Replace all occurrences of 'what' with this
 * @return true Something has been replaced
 * @return false Nothing has been replaced
 */
bool ReplaceAll(std::string& inOutStr, const std::string_view& what,
                const std::string_view& with)
{
    size_t count = 0;
    for (std::string::size_type pos{};
         inOutStr.npos
         != (pos = inOutStr.find(what.data(), pos, what.length()));
         pos += with.length(), count++)
    {
        inOutStr.replace(pos, what.length(), with.data(), with.length());
    }
    return static_cast<bool>(count);
}

/**
 * @brief Reduce by removing all matched brackets
 *
 * @param line Line from text file
 * @return std::string& Modified line
 */
static std::string& Reduce(std::string& line)
{
    while (ReplaceAll(line, "()", "") || ReplaceAll(line, "[]", "")
           || ReplaceAll(line, "{}", "") || ReplaceAll(line, "<>", ""))
    {
    }
    return line;
}

/**
 * @brief Find the first closing bracket for a simplified/reduced input
 *
 * @param line Line to find if there is illegal closing bracket
 * @return char the illegal closing bracket, otherwise '\0'
 */
char FindIllegalChar(std::string& line)
{
    line = Reduce(line);

    for (const auto& ch : line)
    {
        if (ch == ')')
        {
            return ')';
        }
        if (ch == ']')
        {
            return ']';
        }
        if (ch == '}')
        {
            return '}';
        }
        if (ch == '>')
        {
            return '>';
        }
    }
    return '\0';
}

/**
 * @brief Solve part 1
 *
 * @param lines Data from text file
 * @return int Solution
 */
static int Part1(std::vector<std::string>& lines)
{
    const int curlyScore = 3;
    const int squareScore = 57;
    const int squigglyScore = 1197;
    const int angledScore = 25137;

    int curlyError = 0;
    int squareError = 0;
    int squigglyError = 0;
    int angledError = 0;

    for (auto i = lines.begin(); i != lines.end();)
    {
        auto& line = *i;
        char illegalChar = FindIllegalChar(line);
        if (illegalChar)
        {
            switch (illegalChar)
            {
            case ')':
                curlyError++;
                break;

            case ']':
                squareError++;
                break;

            case '}':
                squigglyError++;
                break;

            case '>':
                angledError++;
                break;

            default:
                break;
            }
            i = lines.erase(i);
        }
        else
        {
            i++;
        }
    }

    int points = curlyError * curlyScore;
    points += squareError * squareScore;
    points += squigglyError * squigglyScore;
    points += angledError * angledScore;
    return points;
}

/**
 * @brief Solve part 2
 *
 * @param lines data from text file
 * @return long int Solution will be large int
 */
static int64_t Part2(std::vector<std::string> lines)
{
    std::vector<int64_t> scores(lines.size(), 0L);
    for (size_t i = 0; i < lines.size(); i++)
    {
        for (auto j = lines[i].rbegin(); j != lines[i].rend(); j++)
        {
            scores[i] *= 5;
            switch (*j)
            {
            case '(':
                scores[i] += 1;
                break;

            case '[':
                scores[i] += 2;
                break;

            case '{':
                scores[i] += 3;
                break;

            case '<':
                scores[i] += 4;
                break;

            default:
                break;
            }
        }
    }
    const size_t centreIdx = scores.size() / 2;
    std::nth_element(scores.begin(), scores.begin() + centreIdx, scores.end());
    return scores[centreIdx];
}

/**
 * @brief Day 10 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day10(const char* fileName)
{
    std::string text = ReadTextFile(fileName);
    auto splitText = SplitLines(text);
    std::cout << "Part 1: " << Part1(splitText) << "\n";
    std::cout << "Part 2: " << Part2(splitText) << "\n";
}
