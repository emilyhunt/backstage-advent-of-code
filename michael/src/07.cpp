/**
 * @file 07.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 7
 * @version 1.0.0
 * @date 2021-12-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Solve part 1
 *
 * @param numbers to calculate answer from
 * @return int the solution to part 1
 */
static int Part1(const std::vector<int>& numbers)
{
    const int median = Median(numbers);
    int answer = 0;

    for (auto i : numbers)
    {
        answer += std::abs(median - i);
    }

    return answer;
}

/**
 * @brief Solve part 2
 *
 * @param numbers to calculate answer from
 * @return int the solution to part 2
 */
static int Part2(const std::vector<int>& numbers)
{
    const int mean = Mean(numbers);
    int answer = 0;

    for (auto i : numbers)
    {
        int x = std::abs(mean - i);
        answer += (x * (x + 1)) / 2;
    }
    return answer;
}

/**
 * @brief Day 7 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day07(const char* fileName)
{
    std::vector<int> numbers = ReadNumbersFile(fileName);
    std::cout << "Part 1: " << Part1(numbers) << "\n";
    std::cout << "Part 2: " << Part2(numbers) << "\n";
}
