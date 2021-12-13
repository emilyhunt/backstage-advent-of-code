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

void Fold(std::vector<std::vector<bool>>& grid,
          std::pair<FoldDirection, int> fold)
{
}

std::string GridToString(const std::vector<std::vector<bool>>& grid)
{
    std::stringstream ss;
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j])
                ss << "#";
            else
                ss << ".";
        }
        ss << "\n";
    }
    return ss.str();
}

static std::string
Part1(const std::pair<std::list<std::pair<int, int>>,
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

    return GridToString(grid);
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
    // PrintPaperAndInstructions(data);

    std::cout << "Part 1:\n" << Part1(data) << "\n";
}
