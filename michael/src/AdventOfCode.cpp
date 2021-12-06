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
 * @param argc Count of arguments, includes the command running the program itself
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

    int dayId = std::atoi(argv[1]);
    switch (dayId)
    {
    case 1:
        Day1(argv[2]);
        break;

    case 2:
        Day2(argv[2]);
        break;

    case 3:
        Day3(argv[2]);
        break;

    case 4:
        Day4(argv[2]);
        break;

    case 5:
        Day5(argv[2]);
        break;

    case 6:
        Day6(argv[2]);
        break;

    case 7:
        Day7(argv[2]);
        break;

    default:
        throw std::invalid_argument(argv[1]);
        break;
    }
}