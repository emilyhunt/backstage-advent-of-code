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
#include <stack>
#include <string>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Definitions
================================================================================
*/
static std::unordered_map<std::string, int> cost{
    {"A", 1}, {"B", 10}, {"C", 100}, {"D", 1000}};

/**
 * @brief Solution to part 1, solved by hand
 *
 * @return int Solution
 */
static int Part1()
{
    int answer = 2 * cost["D"];
    answer += 3 * cost["A"];
    answer += 3 * cost["D"];
    answer += 6 * cost["A"];
    answer += 5 * cost["D"];
    answer += 5 * cost["C"];
    answer += 5 * cost["C"];
    answer += 5 * cost["B"];
    answer += 5 * cost["B"];
    answer += 3 * cost["A"];
    answer += 8 * cost["A"];

    return answer;
}

static int Part2()
{
    // #############
    // #EF.G.H.I.JK#
    // ###A#B#C#D###
    //   #.#.#.#.#
    //   #.#.#.#.#
    //   #.#.#.#.#
    //   #########

    std::unordered_map<std::string, std::vector<std::string>> puzzleMap{
        {"A", {"F", "G"}},
        {"B", {"G", "H"}},
        {"C", {"H", "I"}},
        {"D", {"I", "J"}},
        {"E", {"F"}},
        {"F", {"A", "G"}},
        {"G", {"F", "A", "B", "H"}},
        {"H", {"G", "B", "C", "I"}},
        {"I", {"H", "C", "D", "J"}},
        {"J", {"I", "D"}},
        {"K", {"J"}},
    };

    std::array<std::stack<char>, 4> destinations;

    int answer = 0;

    // destinations[0].emplace("B", "D", "D", "B");
    // destinations[1].emplace("C", "C", "B", "C");
    // destinations[2].emplace("A", "B", "A", "D");
    // destinations[3].emplace("D", "A", "C", "A");

    // std::cout << destinations[2].top() << "\n";

    return answer;
}

// 68796 too high!
// 42286 wrong
// 45058 too low!
// 42226 too low!

// Lower bound: 35040

/**
 * @brief Day 23 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day23(const char* fileName)
{
    bool printMaps = false;
    std::string text = ReadTextFile(fileName);

    if (printMaps)
        std::cout << "Puzzle:\n" << text << "\n\n";
    std::cout << "Part 1: " << Part1() << "\n";

    text.insert(42, "  #D#C#B#A#\n  #D#B#A#C#\n");

    if (printMaps)
        std::cout << "Puzzle:\n" << text << "\n\n";
    std::cout << "Part 2: " << Part2() << "\n";
}
