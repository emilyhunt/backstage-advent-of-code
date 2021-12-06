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

#include <iostream>
#include <string>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Declarations
================================================================================
*/
int Part1();
int Part2();

/*
================================================================================
                            Function Definitions
================================================================================
*/
int Part1() { return 0; }
int Part2() { return 0; }

/**
 * @brief Day 7 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day7(const char* fileName)
{
    std::string text = ReadTextFile(fileName);
    std::cout << text << "\n";

    std::cout << "Part 1: " << Part1() << "\n";
    std::cout << "Part 2: " << Part2() << "\n";
}
