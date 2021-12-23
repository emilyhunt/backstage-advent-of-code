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
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Definitions
================================================================================
*/
static std::unordered_map<char, int> cost{
    {'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000}};

/**
 * @brief Solution to part 1, solved by hand
 *
 * @return int Solution
 */
static int Part1()
{
    int answer = 2 * cost['D'];
    answer += 3 * cost['A'];
    answer += 3 * cost['D'];
    answer += 6 * cost['A'];
    answer += 5 * cost['D'];
    answer += 5 * cost['C'];
    answer += 5 * cost['C'];
    answer += 5 * cost['B'];
    answer += 5 * cost['B'];
    answer += 3 * cost['A'];
    answer += 8 * cost['A'];

    return answer;
}

using PuzzleGrid = std::array<std::string, 11>;

namespace std
{
/**
 * @brief Hash function for PuzzleGrid
 */
template <>
struct hash<PuzzleGrid>
{
    /**
     * @brief Call operator for hash object, for use with std::unordered_map
     *
     * @param grid PuzzleGrid object to hash
     * @return std::size_t hash of object
     */
    std::size_t operator()(const PuzzleGrid& grid) const
    {
        std::stringstream ss;
        for (const auto& elem : grid)
            ss << elem;
        return std::hash<std::string>{}(ss.str());
    }
};
}

static int Part2()
{
    // #############
    // #01.3.5.7.9A#
    // ###2#4#6#8###
    //   #.#.#.#.#
    //   #.#.#.#.#
    //   #.#.#.#.#
    //   #########

    int totalCost = 0;
    PuzzleGrid start{".",    ".", "BDDB", ".", "CBCC", ".",
                     "DABA", ".", "ACAD", ".", "."};
    PuzzleGrid end{".",    ".", "AAAA", ".", "BBBB", ".",
                   "CCCC", ".", "DDDD", ".", "."};

    std::queue<PuzzleGrid> frontier;
    frontier.push(start);
    std::unordered_set<PuzzleGrid> visited{start};

    std::array<int, 2> searchDirs{-1, 1};
    std::array<std::size_t, 4> columns{2, 4, 6, 8};

    while (!frontier.empty())
    {
        PuzzleGrid current = frontier.front();
        frontier.pop();

        // Expand
        for (size_t i = 0; i < current.size(); i++)
        {
            for (const auto& searchDir : searchDirs)
            {
                int index = i + searchDir;
                // If nothing here or out of bounds
                if ((index < 0) || (index >= static_cast<int>(current.size()))
                    || (current[i] == "."))
                    continue;

                // If moving to a column and it's full
                if (current[index].length() == 4)
                    continue;

                // If moving to waiting area but it's full
                if (!std::count(columns.begin(), columns.end(), index)
                    && !(current[index] == "."))
                    continue;

                PuzzleGrid next = current;

                char letter = current[i][current[i].size() - 1];

                if (next[index].length() == 1)
                    next[index].pop_back();
                next[index].push_back(letter);
                next[i].pop_back();
                if (next[i].length() == 0)
                    next[i].push_back('.');

                if (!visited.count(next))
                {
                    frontier.push(next);
                    visited.insert(next);
                }

                totalCost += cost[letter];

                if (next == end)
                    return totalCost;

                // PrintVector(next);
            }
        }
    }

    // std::unordered_map<std::string, std::vector<std::string>> puzzleMap{
    //     {"A", {"F", "G"}},
    //     {"B", {"G", "H"}},
    //     {"C", {"H", "I"}},
    //     {"D", {"I", "J"}},
    //     {"E", {"F"}},
    //     {"F", {"A", "G"}},
    //     {"G", {"F", "A", "B", "H"}},
    //     {"H", {"G", "B", "C", "I"}},
    //     {"I", {"H", "C", "D", "J"}},
    //     {"J", {"I", "D"}},
    //     {"K", {"J"}},
    // };

    return totalCost;
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
    bool printMaps = true;
    std::string text = ReadTextFile(fileName);

    if (printMaps)
        std::cout << "Puzzle:\n" << text << "\n\n";
    std::cout << "Part 1: " << Part1() << "\n";

    text.insert(42, "  #D#C#B#A#\n  #D#B#A#C#\n");

    if (printMaps)
        std::cout << "Puzzle:\n" << text << "\n\n";
    std::cout << "Part 2: " << Part2() << "\n";
}
