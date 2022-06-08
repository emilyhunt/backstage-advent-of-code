/**
 * @file 22.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 22
 * @version 1.0.0
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <array>
#include <iostream>
#include <iterator>
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
/// 3D Coordinate structure made from length 3 array
using Coordinate = std::array<int64_t, 3>;

/// Cuboid structure from pair of coordinates
using Cuboid = std::pair<Coordinate, Coordinate>;

/// Instructions, a vector of bool and cuboids
using Instructions = std::vector<std::pair<bool, Cuboid>>;

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Parse instructions in text file to data structure
 *
 * @param text from file
 * @return Data parsed into data structure
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

        instructions.push_back({switchState, {rangeStart, rangeEnd}});
    }

    return instructions;
}

/**
 * @brief Get the area of a cuboid
 *
 * @param cuboid to get area of
 * @return Total area of cuboid
 */
int64_t GetArea(const Cuboid& cuboid)
{
    const auto& [coord0, coord1] = cuboid;

    const auto& [x0, y0, z0] = coord0;
    const auto& [x1, y1, z1] = coord1;

    return (x1 - x0) * (y1 - y0) * (z1 - z0);
}

/**
 * @brief Print Cuboid to ostream
 *
 * @param os ostream to print to
 * @param cuboid to be printed
 * @return Modified ostream reference
 */
std::ostream& operator<<(std::ostream& os, const Cuboid& cuboid)
{
    const auto& [coord0, coord1] = cuboid;

    const auto& [x0, y0, z0] = coord0;
    const auto& [x1, y1, z1] = coord1;

    os << "x=" << x0 << ".." << x1 << ",";
    os << "y=" << y0 << ".." << y1 << ",";
    os << "z=" << z0 << ".." << z1 << " == " << GetArea(cuboid);
    return os;
}

/**
 * @brief Print Instructions to ostream
 *
 * @param os ostream to print to
 * @param instructions to be printed
 * @return Modified ostream reference
 */
std::ostream& operator<<(std::ostream& os, const Instructions& instructions)
{
    for (const auto& [switchVal, cuboid] : instructions)
    {
        if (switchVal)
            os << "on ";
        else
            os << "off ";

        os << cuboid << "\n";
    }
    return os;
}

bool IsEndOfIteration(const std::set<int64_t>::const_iterator& iter,
                      const std::set<int64_t>& set, int64_t endVal)
{
    if (*iter == *set.rbegin())
        return true;
    if (*iter > endVal)
        return true;
    return false;
}

/**
 * @brief Solve part 1
 *
 * @param instructions from input file
 * @return Solution to part of puzzle
 */
static size_t Part1(const Instructions& instructions)
{
    std::set<Coordinate> onCubes{};

    for (const auto& [switchState, cuboid] : instructions)
    {
        const auto& [rangeStart, rangeEnd] = cuboid;
        for (int64_t x = rangeStart[0]; x <= rangeEnd[0]; x++)
        {
            if (x < -50)
                continue;
            if (x > 50)
                break;
            for (int64_t y = rangeStart[1]; y <= rangeEnd[1]; y++)
            {
                if (y < -50)
                    continue;
                if (y > 50)
                    break;
                for (int64_t z = rangeStart[2]; z <= rangeEnd[2]; z++)
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
 * @brief Solve part 2
 *
 * @param instructions from input file
 * @return Solution to part of puzzle
 */
static size_t Part2(const Instructions& instructions)
{
    std::set<Cuboid> cuboids{};

    std::array<std::set<int64_t>, 3> partitions{};

    // Find boarders for coordinate compression
    for (const auto& [switchState, cuboid] : instructions)
    {
        const auto& [startCoord, endCoord] = cuboid;
        for (size_t i = 0; i < partitions.size(); i++)
        {
            partitions[i].insert(startCoord[i]);
            partitions[i].insert(endCoord[i] + 1);
        }
    }

    for (const auto& [switchState, cuboid] : instructions)
    {
        const auto& [startCoord, endCoord] = cuboid;

        for (auto xIter = partitions[0].find(startCoord[0]);
             !IsEndOfIteration(xIter, partitions[0], endCoord[0]); xIter++)
        {
            for (auto yIter = partitions[1].find(startCoord[1]);
                 !IsEndOfIteration(yIter, partitions[1], endCoord[1]); yIter++)
            {
                for (auto zIter = partitions[2].find(startCoord[2]);
                     !IsEndOfIteration(zIter, partitions[2], endCoord[2]);
                     zIter++)
                {
                    Cuboid newCuboid = {{*xIter, *yIter, *zIter},
                                        {*std::next(xIter), *std::next(yIter),
                                         *std::next(zIter)}};

                    if (switchState)
                        cuboids.insert(newCuboid);
                    else
                        cuboids.erase(newCuboid);
                }
            }
        }
    }

    size_t sum = 0;

    for (const auto& cuboid : cuboids)
        sum += GetArea(cuboid);

    return sum;
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
    std::cout << "Part 2: " << Part2(instructions) << "\n";
}
