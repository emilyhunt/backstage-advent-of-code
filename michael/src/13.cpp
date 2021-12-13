/**
 * @file 13.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 13
 * @version 1.0.0
 * @date 2021-12-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <list>
#include <regex>
#include <sstream>
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
/**
 * @brief Axis to fold in
 *
 */
enum class FoldDirection
{
    X,
    Y
};

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Convert text into data structure as lists of coords and folds
 *
 * @param text File input text
 * @return std::pair<std::list<std::pair<int, int>>,
 * std::list<std::pair<FoldDirection, int>>> Pair of lists for coords and folds
 */
std::pair<std::list<std::pair<int, int>>,
          std::list<std::pair<FoldDirection, int>>>
GetPaperAndInstructions(const std::string& text)
{
    std::pair<std::list<std::pair<int, int>>,
              std::list<std::pair<FoldDirection, int>>>
        data;

    std::regex coordsRegex("(\\d+),(\\d+)");
    std::regex foldsRegex("fold along (\\w)=(\\d+)");
    std::smatch match;
    auto coordsBegin
        = std::sregex_iterator(text.begin(), text.end(), coordsRegex);
    auto foldsBegin
        = std::sregex_iterator(text.begin(), text.end(), foldsRegex);
    const auto end = std::sregex_iterator();

    for (auto i = coordsBegin; i != end; i++)
    {
        match = *i;
        data.first.push_back(std::make_pair(std::stoi(match[1].str()),
                                            std::stoi(match[2].str())));
    }

    for (auto i = foldsBegin; i != end; i++)
    {
        match = *i;
        FoldDirection foldDirection;
        if (match[1].str() == "x")
            foldDirection = FoldDirection::X;
        else
            foldDirection = FoldDirection::Y;

        data.second.push_back(
            std::make_pair(foldDirection, std::stoi(match[2].str())));
    }

    return data;
}

/**
 * @brief Print file data to console, should output similar to actual file
 *
 * @param data to be printed
 */
void PrintPaperAndInstructions(
    const std::pair<std::list<std::pair<int, int>>,
                    std::list<std::pair<FoldDirection, int>>>& data)
{
    const auto& [coords, folds] = data;
    for (const auto& coord : coords)
        std::cout << coord.first << "," << coord.second << "\n";

    for (const auto& fold : folds)
    {
        std::string foldDirection;
        if (fold.first == FoldDirection::X)
            foldDirection = "x";
        else
            foldDirection = "y";
        std::cout << foldDirection << ":" << fold.second << "\n";
    }
}

/**
 * @brief Fold the grid
 *
 * @param grid Grid to be folded
 * @param fold Fold instruction
 */
void Fold(std::vector<std::vector<bool>>& grid,
          std::pair<FoldDirection, int> fold)
{
    if (fold.first == FoldDirection::X)
    {
        size_t i, j;
        for (size_t row = 0; row < grid.size(); row++)
        {
            for (i = fold.second + 1, j = fold.second - 1; i < grid[0].size();
                 i++, j--)
            {
                grid[row][j] = grid[row][j] | grid[row][i];
            }
        }
        for (auto& row : grid)
            row.erase(row.begin() + fold.second, row.end());
    }
    else
    {
        size_t i, j;
        for (i = fold.second + 1, j = fold.second - 1; i < grid.size();
             i++, j--)
            for (size_t col = 0; col < grid[0].size(); col++)
                grid[j][col] = grid[j][col] | grid[i][col];

        grid.erase(grid.begin() + fold.second, grid.end());
    }
}

/**
 * @brief Represent the grid as a string
 *
 * @param grid Grid to be converted to string
 * @return std::string Grid as a #/. grid
 */
std::string GridToString(const std::vector<std::vector<bool>>& grid)
{
    std::stringstream ss;
    for (const auto& row : grid)
    {
        for (const auto& element : row)
        {
            if (element)
                ss << "#";
            else
                ss << ".";
        }
        ss << "\n";
    }
    return ss.str();
}

/**
 * @brief Solve and print part 1 and 2
 *
 * @param data Data extracted from file
 * @return None
 */
static void
Part1And2(const std::pair<std::list<std::pair<int, int>>,
                          std::list<std::pair<FoldDirection, int>>>& data)
{
    const auto& [coords, folds] = data;

    int maxX = 1;
    int maxY = 1;
    for (const auto& [x, y] : coords)
    {
        maxX = std::max(maxX, x + 1);
        maxY = std::max(maxY, y + 1);
    }
    std::vector<std::vector<bool>> grid(maxY, std::vector<bool>(maxX, false));

    for (const auto& [x, y] : coords)
        grid[y][x] = true;

    Fold(grid, *folds.begin());

    std::string output(GridToString(grid));

    std::cout << "Part 1: " << std::count(output.begin(), output.end(), '#')
              << "\n";

    for (auto i = ++folds.begin(); i != folds.end(); i++)
    {
        Fold(grid, *i);
    }

    std::cout << "Part 2:\n" << GridToString(grid) << "\n";
}

/**
 * @brief Day 13 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day13(const char* fileName)
{
    const std::string text = ReadTextFile(fileName);
    auto data = GetPaperAndInstructions(text);
    Part1And2(data);
}
