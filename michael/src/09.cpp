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

int Part1(const std::vector<std::vector<int>>& numberGrid)
{
    int sum = 0;
    const size_t lastCol = numberGrid[0].size() - 1;
    const size_t lastRow = numberGrid.size() - 1;

    // Corners
    if (numberGrid[0][0] < numberGrid[0][1]
        && numberGrid[0][0] < numberGrid[1][0])
        sum += GetRiskLevel(numberGrid, 0, 0);

    if (numberGrid[0][lastCol] < numberGrid[0][lastCol - 1]
        && numberGrid[0][lastCol] < numberGrid[1][lastCol])
        sum += GetRiskLevel(numberGrid, 0, lastCol);

    if (numberGrid[lastRow][0] < numberGrid[lastRow][1]
        && numberGrid[lastRow][0] < numberGrid[lastRow - 1][0])
        sum += GetRiskLevel(numberGrid, lastRow, 0);

    if (numberGrid[lastRow][lastCol] < numberGrid[lastRow][lastCol - 1]
        && numberGrid[lastRow][lastCol] < numberGrid[lastRow - 1][lastCol])
        sum += GetRiskLevel(numberGrid, lastRow, lastCol);

    // Edges
    for (size_t row = 1; row < numberGrid.size() - 1; row++)
        if (numberGrid[row][0] < numberGrid[row - 1][0]
            && numberGrid[row][0] < numberGrid[row + 1][0]
            && numberGrid[row][0] < numberGrid[row][1])
            sum += GetRiskLevel(numberGrid, row, 0);

    for (size_t row = 1; row < numberGrid.size() - 1; row++)
        if (numberGrid[row][lastCol] < numberGrid[row - 1][lastCol]
            && numberGrid[row][lastCol] < numberGrid[row + 1][lastCol]
            && numberGrid[row][lastCol] < numberGrid[row][lastCol - 1])
            sum += GetRiskLevel(numberGrid, row, lastCol);

    for (size_t col = 1; col < numberGrid[0].size() - 1; col++)
        if (numberGrid[0][col] < numberGrid[0][col - 1]
            && numberGrid[0][col] < numberGrid[0][col + 1]
            && numberGrid[0][col] < numberGrid[1][col])
            sum += GetRiskLevel(numberGrid, 0, col);

    for (size_t col = 1; col < numberGrid[0].size() - 1; col++)
        if (numberGrid[lastRow][col] < numberGrid[lastRow][col - 1]
            && numberGrid[lastRow][col] < numberGrid[lastRow][col + 1]
            && numberGrid[lastRow][col] < numberGrid[lastRow-1][col])
            sum += GetRiskLevel(numberGrid, lastRow, col);

    // Insides
    for (size_t row = 1; row < numberGrid.size() - 1; row++)
        for (size_t col = 1; col < numberGrid[0].size() - 1; col++)
            if (numberGrid[row][col] < numberGrid[row - 1][col]
                && numberGrid[row][col] < numberGrid[row + 1][col]
                && numberGrid[row][col] < numberGrid[row][col - 1]
                && numberGrid[row][col] < numberGrid[row][col + 1])
                sum += GetRiskLevel(numberGrid, row, col);

    return sum;
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
}
