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
int main(int argc, char** argv)
{
    if (argc < 3)
        throw std::invalid_argument(
            "Too few args, format is ./AdventOfCode <dayId> <inputFile>");
    if (argc > 3)
        throw std::invalid_argument(
            "Too many args, format is ./AdventOfCode <dayId> <inputFile>");

    switch (std::atoi(argv[1]))
    {
    case 1:
        Day01(argv[2]);
        break;

    case 2:
        Day02(argv[2]);
        break;

    case 3:
        Day03(argv[2]);
        break;

    case 4:
        Day04(argv[2]);
        break;

    case 5:
        Day05(argv[2]);
        break;

    case 6:
        Day06(argv[2]);
        break;

    case 7:
        Day07(argv[2]);
        break;

    case 8:
        Day08(argv[2]);
        break;

    case 9:
        Day09(argv[2]);
        break;

    case 10:
        Day10(argv[2]);
        break;

    case 11:
        Day11(argv[2]);
        break;

    case 12:
        Day12(argv[2]);
        break;

    case 13:
        Day13(argv[2]);
        break;

    case 14:
        Day14(argv[2]);
        break;

    case 15:
        Day15(argv[2]);
        break;

    case 16:
        Day16(argv[2]);
        break;

    case 17:
        Day17(argv[2]);
        break;

    case 18:
        Day18(argv[2]);
        break;

    case 19:
        Day19(argv[2]);
        break;

    case 20:
        Day20(argv[2]);
        break;

    case 21:
        Day21(argv[2]);
        break;

    case 22:
        Day22(argv[2]);
        break;

    case 23:
        Day23(argv[2]);
        break;

    case 24:
        Day24(argv[2]);
        break;

    case 25:
        Day25(argv[2]);
        break;

    default:
        throw std::invalid_argument(argv[1]);
        break;
    }
}