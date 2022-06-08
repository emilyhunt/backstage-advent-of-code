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
#include <iomanip>
#include <unordered_map>

#include "Days.h"
#include "Utilities.h"

/// Function mapping for day number
static const std::unordered_map<int, void (*)(const char*)> functionMap{
    {1, Day01},  {2, Day02},  {3, Day03},  {4, Day04},  {5, Day05},
    {6, Day06},  {7, Day07},  {8, Day08},  {9, Day09},  {10, Day10},
    {11, Day11}, {12, Day12}, {13, Day13}, {14, Day14}, {15, Day15},
    {16, Day16}, {17, Day17}, {18, Day18}, {19, Day19}, {20, Day20},
    {21, Day21}, {22, Day22}, {23, Day23}, {24, Day24}, {25, Day25}};

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
    int daySelect;
    if (argc < 2)
    {
        std::cout << "Select the day: ";
        std::cin >> daySelect;
    }
    else
        daySelect = std::atoi(argv[1]);

    if (argc > 3)
        throw std::invalid_argument(
            "Too many args, format is ./AdventOfCode <dayId> <inputFile>");

    const size_t MAX_FILENAME_LEN = 256;
    const char* fileName;
    std::string fileNameStr;
    if (argc <= 2)
    {
        std::stringstream ss;
        ss << "../data/" << std::setfill('0') << std::setw(2) << daySelect
           << "/input.txt";
        ss >> fileNameStr;
        fileName = fileNameStr.c_str();
    }
    else if (std::strlen(argv[2]) > (MAX_FILENAME_LEN - 1))
        throw std::length_error("Input file path too long");
    else
        fileName = argv[2];

    functionMap.at(daySelect)(fileName);
    return 0;
}
