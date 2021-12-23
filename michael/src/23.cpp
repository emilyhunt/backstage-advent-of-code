/**
 * @file 23.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 23
 * @version 1.0.0
 * @date 2021-12-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <array>
#include <iostream>
#include <string>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Definitions
================================================================================
*/

/**
 * @brief Solution to part 1, solved by hand
 *
 * @return int Solution
 */
int Part1()
{
    const int A_COST = 1;
    const int B_COST = 10;
    const int C_COST = 100;
    const int D_COST = 1000;
    int answer = 0;

    answer += 2 * D_COST;
    answer += 3 * A_COST;
    answer += 3 * D_COST;
    answer += 6 * A_COST;
    answer += 5 * D_COST;
    answer += 5 * C_COST;
    answer += 5 * C_COST;
    answer += 5 * B_COST;
    answer += 5 * B_COST;
    answer += 3 * A_COST;
    answer += 8 * A_COST;

    return answer;
}

/**
 * @brief Day 23 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day23(const char* fileName)
{
    const std::string text = ReadTextFile(fileName);
    std::cout << "Puzzle:\n" << text << "\n\n";

    std::cout << "Part 1: " << Part1() << "\n";
}
