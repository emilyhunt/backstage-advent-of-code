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
using Instructions = std::vector<std::tuple<bool, Coordinate, Coordinate>>;

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

static size_t Part1(Instructions instructions)
{
    std::set<Coordinate> onCubes{};

    for (const auto& [switchState, rangeStart, rangeEnd] : instructions)
    {
        for (int x = rangeStart[0]; x <= rangeEnd[0]; x++)
        {
            if (x < -50)
                continue;
            if (x > 50)
                break;
            for (int y = rangeStart[1]; y <= rangeEnd[1]; y++)
            {
                if (y < -50)
                    continue;
                if (y > 50)
                    break;
                for (int z = rangeStart[2]; z <= rangeEnd[2]; z++)
                {
                    if (z < -50)
                        continue;
                    if (z > 50)
                        break;

                    if (switchState)
                        onCubes.insert({x, y, z});
                    else
                        onCubes.erase({x, y, z});
                }
            }
        }
    }

    return onCubes.size();
}

/**
 * @brief Day 22 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day22(const char* fileName)
{
    const auto& instructions = ParseInstructions(ReadTextFile(fileName));
    std::cout << "Part 1: " << Part1(instructions) << "\n";
}
