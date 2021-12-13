/**
 * @file 01.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 1
 * @version 1.0.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <numeric>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Declarations
================================================================================
*/
static int Part1(const std::vector<int>& numbers);
static int Part2(const std::vector<int>& numbers);

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Solve part 1
 *
 * @param numbers File input numbers
 * @return int Solution
 */
static int Part1(const std::vector<int>& numbers)
{
    std::vector<int> diff(numbers.size(), 0);
    std::adjacent_difference(numbers.begin(), numbers.end(), diff.begin());

    int sum = 0;
    // Drop first adj diff as it is just the first number again
    for (auto iter = diff.begin() + 1; iter != diff.end(); iter++)
        if (*iter > 0)
            sum += 1;
    return sum;
}

/**
 * @brief Solve part 2
 *
 * @param numbers File input numbers
 * @return int Solution
 */
static int Part2(const std::vector<int>& numbers)
{
    std::vector<int> windowed;
    for (size_t i = 0; i < numbers.size() - 2; i++)
        windowed.push_back(numbers[i] + numbers[i + 1] + numbers[i + 2]);

    return Part1(windowed);
}

/**
 * @brief Day 1 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day01(const char* fileName)
{
    std::vector<int> numbers = ReadNumbersFile<int>(fileName);
    std::cout << "Part 1: " << Part1(numbers) << "\n";
    std::cout << "Part 2: " << Part2(numbers) << "\n";
}
