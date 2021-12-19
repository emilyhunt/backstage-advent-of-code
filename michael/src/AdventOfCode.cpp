/**
 * @file AdventOfCode.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Program starts from here and calls the relavant function for each day
 * @version 1.0.0
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <exception>
#include <unordered_map>

#include "Days.h"
#include "Utilities.h"

/**
 * @brief Start of program execution
 *
 * @param argc Count of arguments, includes the command running the program
 * itself
 * @param argv Arguments, first is always the program itself
 * @return int Return 0 for normal exit
 */
int main(int argc, char **argv)
{
    if (argc < 2)
        throw std::invalid_argument(
            "Too few args, format is ./AdventOfCode <dayId> <inputFile>");
    if (argc > 3)
        throw std::invalid_argument(
            "Too many args, format is ./AdventOfCode <dayId> <inputFile>");

    const auto select = std::atoi(argv[1]);
    if ((select < 1) || (select > 25))
        throw std::invalid_argument("Only days 1 to 25, no more, no less");

    char fileName[32] = {};

    if (argc == 2)
    {
        const char *fileNameBase = "data/xx/input.txt";
        std::strcpy(fileName, fileNameBase);
        fileName[5] = (select / 10) + '0';
        fileName[6] = (select % 10) + '0';
    }
    else
        std::strcpy(fileName, argv[2]);

    std::unordered_map<int, void (*)(const char *)> functionMap{{1, Day01},
    {2, Day02}, {3, Day03}, {4, Day04}, {5, Day05}, {6, Day06}, {7, Day07},
    {8, Day08}, {9, Day09}, {10, Day10}, {11, Day11}, {12, Day12}, {13, Day13},
    {14, Day14}, {15, Day15}, {16, Day16}, {17, Day17}, {18, Day18},
    {19, Day19}, {20, Day20}, {21, Day21}, {22, Day22}, {23, Day23},
    {24, Day24}, {25, Day25}};

    functionMap[select](fileName);

    return 0;
}
