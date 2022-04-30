/**
 * @file 06.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 6
 * @version 1.0.0
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <deque>
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
void SimulateDay(std::deque<int64_t>& lanternfish);
int64_t CountFish(const std::deque<int64_t>& lanternfish);
std::deque<int64_t> ConvertToCounts(const std::vector<int>& lanternfish);
int64_t SimulateLanternfish(const std::vector<int>& lanternfish, int steps);

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Simulate a single day of fish spawing
 *
 * @param lanternfish Previous day of fish, is modified by function
 */
void SimulateDay(std::deque<int64_t>& lanternfish)
{
    int64_t countAtZero = lanternfish.front();
    lanternfish.pop_front();
    lanternfish[6] += countAtZero;
    lanternfish.push_back(countAtZero);
}

/**
 * @brief Count the total number of fish
 *
 * @param lanternfish Fish record
 * @return long int Count of fish
 */
int64_t CountFish(const std::deque<int64_t>& lanternfish)
{
    int64_t startingVal = 0;
    return std::accumulate(lanternfish.begin(), lanternfish.end(), startingVal);
}

/**
 * @brief Convert a vector of fish ages to counts of fish at each age
 *
 * @param lanternfish Vector of fish ages
 * @return std::deque<long int> Count of fish at each age
 */
std::deque<int64_t> ConvertToCounts(const std::vector<int>& lanternfish)
{
    std::deque<int64_t> countedFish;
    for (int i = 0; i < 9; i++)
        countedFish.push_back(
            std::count(lanternfish.begin(), lanternfish.end(), i));
    return countedFish;
}

/**
 * @brief Simulate fish growth over specified days and return total fish
 *
 * @param lanternfish Fish vector in beginning of simulation
 * @param steps Number of steps or days to simulate over
 * @return long int Amount of fish at end of simulation
 */
int64_t SimulateLanternfish(const std::vector<int>& lanternfish, int steps)
{
    std::deque<int64_t> fishes = ConvertToCounts(lanternfish);

    for (int i = 0; i < steps; i++)
        SimulateDay(fishes);

    return CountFish(fishes);
}

/**
 * @brief Day 6 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day06(const char* fileName)
{
    std::vector<int> lanternfish = ReadNumbersFile<int>(fileName);

    std::cout << "Part 1: " << SimulateLanternfish(lanternfish, 80) << "\n";
    std::cout << "Part 2: " << SimulateLanternfish(lanternfish, 256) << "\n";
}
