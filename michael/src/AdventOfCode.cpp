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

    switch (select)
    {
    case 1:
        Day01(fileName);
        break;

    case 2:
        Day02(fileName);
        break;

    case 3:
        Day03(fileName);
        break;

    case 4:
        Day04(fileName);
        break;

    case 5:
        Day05(fileName);
        break;

    case 6:
        Day06(fileName);
        break;

    case 7:
        Day07(fileName);
        break;

    case 8:
        Day08(fileName);
        break;

    case 9:
        Day09(fileName);
        break;

    case 10:
        Day10(fileName);
        break;

    case 11:
        Day11(fileName);
        break;

    case 12:
        Day12(fileName);
        break;

    case 13:
        Day13(fileName);
        break;

    case 14:
        Day14(fileName);
        break;

    case 15:
        Day15(fileName);
        break;

    case 16:
        Day16(fileName);
        break;

    case 17:
        Day17(fileName);
        break;

    case 18:
        Day18(fileName);
        break;

    case 19:
        Day19(fileName);
        break;

    case 20:
        Day20(fileName);
        break;

    case 21:
        Day21(fileName);
        break;

    case 22:
        Day22(fileName);
        break;

    case 23:
        Day23(fileName);
        break;

    case 24:
        Day24(fileName);
        break;

    case 25:
        Day25(fileName);
        break;

    default:
        throw std::invalid_argument(argv[1]);
        break;
    }
}
