/**
 * @file 24.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 24
 * @version 1.0.0
 * @date 2021-12-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Checks if the number has a zero digit
 *
 * @param input Number to check
 * @return true There is a zero digit
 * @return false There is not a zero digit
 */
bool ContainsZeroDigit(int64_t input)
{
    while (input > 0)
    {
        int digit = input % 10;
        if (!digit)
            return true;
        input /= 10;
    }

    return false;
}

/**
 * @brief Runs the input program
 *
 * Input is hardcoded so it can be optimised by the compiler.
 *
 * @param digit Array of digits for the 14 digit number
 * @return int Result of z register from the program
 */
int64_t RunProgram(std::array<int64_t, 14> digit)
{
    int64_t w, x, y, z;
    w = x = y = z = 0;

    w = digit[0];
    x += 14;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 8;
    y *= x;
    z += y;

    w = digit[1];
    x *= 0;
    x += z;
    x %= 26;
    x += 15;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 11;
    y *= x;
    z += y;

    w = digit[2];
    x *= 0;
    x += z;
    x %= 26;
    x += 13;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 2;
    y *= x;
    z += y;

    w = digit[3];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -10;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 11;
    y *= x;
    z += y;

    w = digit[4];
    x *= 0;
    x += z;
    x %= 26;
    x += 14;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 1;
    y *= x;
    z += y;

    w = digit[5];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -3;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 5;
    y *= x;
    z += y;

    w = digit[6];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -14;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 10;
    y *= x;
    z += y;

    w = digit[7];
    x *= 0;
    x += z;
    x %= 26;
    x += 12;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 6;
    y *= x;
    z += y;

    w = digit[8];
    x *= 0;
    x += z;
    x %= 26;
    x += 14;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 1;
    y *= x;
    z += y;

    w = digit[9];
    x *= 0;
    x += z;
    x %= 26;
    x += 12;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 11;
    y *= x;
    z += y;

    w = digit[10];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -6;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 9;
    y *= x;
    z += y;

    w = digit[11];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -6;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 14;
    y *= x;
    z += y;

    w = digit[12];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -2;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 11;
    y *= x;
    z += y;

    w = digit[13];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -9;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 2;
    y *= x;
    z += y;

    return z;
}

/**
 * @brief Check the model number if it is invalid
 *
 * @param input Number to check
 * @return true Number is an invalid model number
 * @return false Number is a valid model number
 */
bool CheckModelNumberInvalid(int64_t input)
{
    if (ContainsZeroDigit(input))
        return true;

    std::array<int64_t, 14> digits = {};
    int i = static_cast<int>(digits.size()) - 1;

    while (input > 0)
    {
        digits[i--] = input % 10;
        input /= 10;
    }

    return RunProgram(digits);
}

/**
 * @brief Solves part 1 of the puzzle
 *
 * @return int64_t Solution as in interger
 */
static int64_t Part1()
{
    int64_t modelNumber = 99919770000000; // Close to answer to save time

    while (CheckModelNumberInvalid(modelNumber))
        modelNumber--;

    return modelNumber;
}

/**
 * @brief Solves part 2 of the puzzle
 *
 * @return int64_t Solution as in interger
 */
static int64_t Part2()
{
    int64_t modelNumber = 24913111111111; // Close to answer to save time

    while (CheckModelNumberInvalid(modelNumber))
        modelNumber++;

    return modelNumber;
}

/**
 * @brief Day 24 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day24(const char* fileName)
{
    (void)fileName;

    std::cout << "Part 1: " << Part1() << "\n";
    std::cout << "Part 2: " << Part2() << "\n";
}
