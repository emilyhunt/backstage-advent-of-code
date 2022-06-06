/**
 * @file 22.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 22
 * @version 1.0.0
 * @date 2021-12-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <array>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Classes
================================================================================
*/
using Coordinate = std::array<int, 3>;
using Instruction = std::tuple<bool, Coordinate, Coordinate>;
using Instructions = std::vector<Instruction>;

/*
================================================================================
                            Function Definitions
================================================================================
*/

Instructions ParseInstructions(const std::string& text)
{
    const auto& lines = SplitLines(text);
    Instructions instructions;

    for (const auto& line : lines)
    {
        const auto& switchAndCoords = Split(line, " ");
        bool switchState = switchAndCoords[0] == "on";

        const auto& coords = Split(switchAndCoords[1], ",");

        Coordinate rangeStart{}, rangeEnd{};
        size_t i = 0;
        for (const auto& dimension : coords)
        {
            const auto& numbers = Split(dimension.substr(2), "..");
            rangeStart[i] = std::stoi(numbers[0]);
            rangeEnd[i] = std::stoi(numbers[1]);
            i++;
        }

        instructions.push_back({switchState, rangeStart, rangeEnd});
    }

    return instructions;
}

std::ostream& operator<<(std::ostream& os, Instructions instructions)
{
    for (const auto& [switchVal, rangeStart, rangeEnd] : instructions)
    {
        if (switchVal)
            os << "on ";
        else
            os << "off ";
        const auto& [x0, y0, z0] = rangeStart;
        const auto& [x1, y1, z1] = rangeEnd;
        os << "x=" << x0 << ".." << x1 << ",";
        os << "y=" << y0 << ".." << y1 << ",";
        os << "z=" << z0 << ".." << z1 << "\n";
    }
    return os;
}

/**
 * @brief Day 22 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day22(const char* fileName)
{
    const std::string text = ReadTextFile(fileName);
    const auto& instructions = ParseInstructions(text);
    std::cout << text << "\n\n";
    std::cout << instructions << "\n";
}
