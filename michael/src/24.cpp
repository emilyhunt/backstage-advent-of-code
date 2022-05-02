/**
 * @file 24.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 24
 * @version 1.0.0
 * @date 2021-12-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Classes
================================================================================
*/

/*
================================================================================
                            Function Definitions
================================================================================
*/

using Instructions
    = std::vector<std::pair<std::string, std::vector<std::string>>>;

static Instructions ExtractInstructions(const std::string& text)
{
    Instructions instructions;
    auto lines = SplitLines(text);
    for (const auto& line : lines)
    {
        auto left = line.substr(0, 3);
        auto right = Split(line.substr(4), " ");

        instructions.push_back(std::make_pair(left, right));
    }

    return instructions;
}

static void PrintInstructions(const Instructions& instructions)
{
    for (const auto& instruction : instructions)
    {
        std::cout << instruction.first << " ";
        for (const auto& item : instruction.second)
            std::cout << item << " ";
        std::cout << "\n";
    }
}

static int Part1(const Instructions& instructions) { return 0; }

/**
 * @brief Day 24 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day24(const char* fileName)
{
    const auto text = ReadTextFile(fileName);
    auto instructions = ExtractInstructions(text);

    PrintInstructions(instructions);

    std::cout << Part1(instructions) << "\n";
}
