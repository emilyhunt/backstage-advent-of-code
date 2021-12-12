/**
 * @file 09.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 9
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

std::vector<std::vector<int>> ParseTextToNumberGrid(const std::string& text)
{
    std::vector<std::vector<int>> numberGrid;
    std::vector<int> line;
    for (const auto& ch : text)
    {
        if (ch == '\n')
        {
            numberGrid.push_back(line);
            line.clear();
        }
        else
            line.push_back(ch - '0');
    }
    numberGrid.push_back(line);
    return numberGrid;
}

void PrintNumberGrid(const std::vector<std::vector<int>>& numberGrid)
{
    for (const auto& line : numberGrid)
    {
        for (const auto& number : line)
        {
            std::cout << number;
        }
        std::cout << "\n";
    }
}

int GetRiskLevel(const std::vector<std::vector<int>>& numberGrid, size_t row,
                 size_t col)
{
    return numberGrid[row][col] + 1;
}

static int Part1(const std::vector<std::vector<int>>& numberGrid)
{
    int sum = 0;

    const size_t numRows = numberGrid.size();
    const size_t numCols = numberGrid[0].size();

    const std::array rowSearch = {0, 1, 0, -1};
    const std::array colSearch = {1, 0, -1, 0};

    for (size_t row = 0; row < numRows; row++)
    {
        for (size_t col = 0; col < numCols; col++)
        {
            bool isLowPoint = true;
            for (size_t k = 0; k < rowSearch.size(); k++)
            {
                int searchRow = row + rowSearch[k];
                int searchCol = col + colSearch[k];
                if ((searchRow >= 0) && (searchRow < static_cast<int>(numRows))
                    && (searchCol >= 0)
                    && (searchCol < static_cast<int>(numCols)))
                    if (numberGrid[row][col]
                        >= numberGrid[searchRow][searchCol])
                        isLowPoint = false;
            }
            if (isLowPoint)
                sum += GetRiskLevel(numberGrid, row, col);
        }
    }

    return sum;
}

static int Part2(const std::vector<std::vector<int>>& numberGrid)
{
    const size_t numRows = numberGrid.size();
    const size_t numCols = numberGrid[0].size();

    const std::array rowSearch = {0, 1, 0, -1};
    const std::array colSearch = {1, 0, -1, 0};

    std::vector<size_t> basinSizes;
    std::set<std::pair<int, int>> visited;

    for (size_t row = 0; row < numRows; row++)
    {
        for (size_t col = 0; col < numCols; col++)
        {
            if (!visited.count(std::make_pair(row, col))
                && (numberGrid[row][col] != 9))
            {
                size_t basinSize = 0;
                std::queue<std::pair<int, int>> frontier;
                frontier.push(std::make_pair(row, col));
                while (frontier.size())
                {
                    auto currentCoord = frontier.front();
                    frontier.pop();
                    if (visited.count(currentCoord))
                        continue;
                    visited.insert(currentCoord);
                    basinSize++;
                    for (size_t k = 0; k < rowSearch.size(); k++)
                    {
                        int searchRow = currentCoord.first + rowSearch[k];
                        int searchCol = currentCoord.second + colSearch[k];
                        if ((searchRow >= 0)
                            && (searchRow < static_cast<int>(numRows))
                            && (searchCol >= 0)
                            && (searchCol < static_cast<int>(numCols)))
                            if (numberGrid[searchRow][searchCol] != 9)
                            {
                                frontier.push(
                                    std::make_pair(searchRow, searchCol));
                            }
                    }
                }
                basinSizes.push_back(basinSize);
            }
        }
    }
    std::sort(basinSizes.rbegin(), basinSizes.rend());
    return basinSizes[0] * basinSizes[1] * basinSizes[2];
}

/**
 * @brief Day 9 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day9(const char* fileName)
{
    std::string text = ReadTextFile(fileName);
    auto numberGrid = ParseTextToNumberGrid(text);
    std::cout << "Part 1: " << Part1(numberGrid) << "\n";
    std::cout << "Part 2: " << Part2(numberGrid) << "\n";
}
