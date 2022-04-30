/**
 * @file 11.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 11
 * @version 1.0.0
 * @date 2021-12-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <array>
#include <iostream>
#include <queue>
#include <set>
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
/**
 * @brief Get the Input Data from the text file
 *
 * @param text from the text file
 * @return std::array<std::array<int, 10>, 10> Fixed array of squid energy
 * levels
 */
std::array<std::array<int, 10>, 10> GetInputData(const std::string text)
{
    std::array<std::array<int, 10>, 10> data{};
    size_t i = 0;
    size_t j = 0;
    for (const auto& ch : text)
    {
        if (ch == '\n')
        {
            i++;
            j = 0;
            continue;
        }
        data[i][j] = ch - '0';
        j++;
    }
    return data;
}

/**
 * @brief Print squid energy level array
 *
 * @param data energy levels of the squids in a fixed array grid
 */
void PrintData(const std::array<std::array<int, 10>, 10>& data)
{
    for (const auto& row : data)
    {
        for (const auto& element : row)
            std::cout << element;
        std::cout << "\n";
    }
    std::cout << "\n";
}

/**
 * @brief Increment all squid energy levels in the grid
 *
 * @param grid energy levels of the squids in a fixed array grid
 */
void IncrementGrid(std::array<std::array<int, 10>, 10>& grid)
{
    for (auto& row : grid)
        for (auto& element : row)
            element++;
}

/**
 * @brief Flash all squids that can be
 *
 * @param grid energy levels of the squids in a fixed array grid
 * @return size_t Amount of squids that flashed
 */
size_t Flash(std::array<std::array<int, 10>, 10>& grid)
{
    size_t flashes = 0;
    int thisFlashes = 0;
    int lastFlashes;

    std::set<std::pair<size_t, size_t>> flashed;
    std::queue<std::pair<size_t, size_t>> flashEffect;

    do
    {
        lastFlashes = thisFlashes;
        for (size_t row = 0; row < 10; row++)
        {
            for (size_t col = 0; col < 10; col++)
            {
                if (grid[row][col] > 9)
                {
                    flashes++;
                    thisFlashes++;
                    flashed.insert(std::make_pair(row, col));
                    grid[row][col] = 0;
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            int checkRow = static_cast<int>(row + i);
                            int checkCol = static_cast<int>(col + j);
                            auto flashCoord
                                = std::make_pair(checkRow, checkCol);
                            if ((checkRow >= 0)
                                && (checkRow < static_cast<int>(grid.size()))
                                && (checkCol >= 0)
                                && (checkCol < static_cast<int>(grid.size())))
                                if (!flashed.count(flashCoord))
                                    flashEffect.push(flashCoord);
                        }
                    }
                }
                while (!flashEffect.empty())
                {
                    auto [checkRow, checkCol] = flashEffect.front();
                    flashEffect.pop();
                    grid[checkRow][checkCol]++;
                }
            }
        }
    } while (lastFlashes - thisFlashes);

    return flashes;
}

/**
 * @brief Solve part 1
 *
 * @param data from text input file
 * @return int Solution
 */
static size_t Part1(const std::array<std::array<int, 10>, 10>& data)
{
    std::array<std::array<int, 10>, 10> grid;
    std::copy(data.begin(), data.end(), grid.begin());
    size_t amountOfFlashes = 0;

    for (size_t i = 0; i < 100; i++)
    {
        IncrementGrid(grid);
        amountOfFlashes += Flash(grid);
    }

    return amountOfFlashes;
}

/**
 * @brief Solve part 2
 *
 * @param data from text input file
 * @return int Solution
 */
static size_t Part2(const std::array<std::array<int, 10>, 10>& data)
{
    std::array<std::array<int, 10>, 10> grid;
    std::copy(data.begin(), data.end(), grid.begin());

    size_t step = 1;
    IncrementGrid(grid);

    while (Flash(grid) != 100)
    {
        step++;
        IncrementGrid(grid);
    }

    return step;
}

/**
 * @brief Day 11 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day11(const char* fileName)
{
    const std::string text = ReadTextFile(fileName);
    auto data = GetInputData(text);

    std::cout << "Part 1: " << Part1(data) << "\n";
    std::cout << "Part 2: " << Part2(data) << "\n";
}
