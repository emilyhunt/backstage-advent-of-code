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

#include <algorithm>
#include <array>
#include <functional>
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
/// Cost mapping
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

/// Puzzle grid object
using PuzzleGrid = std::array<std::string, 11>;

/// Priority queue element
using PriorityElement = std::pair<PuzzleGrid, int>;

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
            ss << elem << "-";
        return std::hash<std::string>{}(ss.str());
    }
};

/**
 * @brief Hash function for enroute ((from, to) pair)
 */
template <>
struct hash<std::pair<int, int>>
{
    /**
     * @brief Call operator for hash object, for use with std::unordered_map
     *
     * @param fromTo std::pair<int, int>& object to hash
     * @return std::size_t hash of object
     */
    std::size_t operator()(const std::pair<int, int>& fromTo) const
    {
        std::stringstream ss;
        ss << fromTo.first << "-" << fromTo.second;
        return std::hash<std::string>{}(ss.str());
    }
};

}

/**
 * @brief Print PuzzleGrid to ostream
 *
 * @param os to print to
 * @param grid to be printed
 * @return std::ostream& to print to
 */
std::ostream& operator<<(std::ostream& os, const PuzzleGrid& grid)
{
    {
        std::array<std::string, 7> row = {".", ".", ".", ".", ".", ".", "."};
        if (grid[0].length())
            row[0] = grid[0];
        if (grid[10].length())
            row[6] = grid[10];

        for (int i = 0; i < 5; i++)
        {
            std::size_t index = (i * 2) + 1;
            if (grid[index].length())
                row[i + 1] = grid[index];
        }

        os << "#############\n#" << row[0] << row[1] << "." << row[2] << "."
           << row[3] << "." << row[4] << "." << row[5] << row[6] << "#\n";
    }
    bool firstRun = true;
    for (int i = 3; i >= 0; i--)
    {
        if (firstRun)
            os << "##";
        else
            os << "  ";

        std::array<char, 4> row = {'.', '.', '.', '.'};
        // = {grid[2][i], grid[4][i], grid[6][i], grid[8][i]};

        for (int j = 0; j < 4; j++)
        {
            int index = (j * 2) + 2;
            if (static_cast<int>(grid[index].length()) > i)
                row[j] = grid[index][i];
        }

        os << "#" << row[0] << "#" << row[1] << "#" << row[2] << "#" << row[3]
           << "#";
        if (firstRun)
        {
            os << "##\n";
            firstRun = false;
        }
        else
            os << "\n";
    }

    os << "  #########";
    return os;
}

/**
 * @brief Print the route found
 *
 * @param cameFrom node route
 * @param costs of each node from start
 * @param end final tile
 */
static void
PrintRoute(const std::unordered_map<PuzzleGrid, PuzzleGrid>& cameFrom,
           const std::unordered_map<PuzzleGrid, int>& costs,
           const PuzzleGrid& end)
{
    std::stack<PuzzleGrid> route;
    route.push(end);

    PuzzleGrid key = end;
    while (cameFrom.count(key))
    {
        key = cameFrom.at(key);
        route.push(key);
    }

    int lastCost = 0;

    while (!route.empty())
    {
        std::cout << route.top() << "\n";
        int cost = costs.at(route.top());
        std::cout << cost << "\n" << cost - lastCost << "\n\n";
        route.pop();
        lastCost = cost;
    }
}

/**
 * @brief Less than operator
 *
 * @param lhs left hand side
 * @param rhs right hand side
 * @return true lhs is less than rhs
 * @return false lsh is not less than rhs
 */
bool operator<(const PriorityElement& lhs, const PriorityElement& rhs)
{
    return lhs.second < rhs.second;
}

/**
 * @brief Greater than operator
 *
 * @param lhs left hand side
 * @param rhs right hand side
 * @return true lhs is greater than rhs
 * @return false lhs is not greater than rhs
 */
bool operator>(const PriorityElement& lhs, const PriorityElement& rhs)
{
    return lhs.second > rhs.second;
}

/**
 * @brief Equal to operator
 *
 * @param lhs left hand side
 * @param rhs right hand side
 * @return true both inputs are equal
 * @return false both inputs are not equal
 */
bool operator==(const PuzzleGrid& lhs, const PuzzleGrid& rhs)
{
    return std::hash<PuzzleGrid>{}(lhs) == std::hash<PuzzleGrid>{}(rhs);
}

/**
 * @brief Not equal to operator
 *
 * @param lhs left hand side
 * @param rhs right hand side
 * @return true both inputs are not equal
 * @return false both inputs are equal
 */
bool operator!=(const PuzzleGrid& lhs, const PuzzleGrid& rhs)
{
    return !(lhs == rhs);
}

/// X postion of tile columns
static const std::array<std::size_t, 4> columns{2, 4, 6, 8};

/**
 * @brief Check if column insertion is allowed
 *
 * @param letter to be test if insertion is allowed
 * @param index x position to move to
 * @param columnContents the preexisting letters in column being moved to
 * @return true The letter can be placed in the column
 * @return false The letter cannot be placed in the column
 */
static bool IsColumnInsertionAllowed(char letter, std::size_t index,
                                     const std::string& columnContents)
{
    switch (letter)
    {
    case 'A':
        return index == columns[0]
               && (columnContents.find('B') == std::string::npos)
               && (columnContents.find('C') == std::string::npos)
               && (columnContents.find('D') == std::string::npos);

    case 'B':
        return index == columns[1]
               && (columnContents.find('A') == std::string::npos)
               && (columnContents.find('C') == std::string::npos)
               && (columnContents.find('D') == std::string::npos);

    case 'C':
        return index == columns[2]
               && (columnContents.find('A') == std::string::npos)
               && (columnContents.find('B') == std::string::npos)
               && (columnContents.find('D') == std::string::npos);

    case 'D':
        return index == columns[3]
               && (columnContents.find('A') == std::string::npos)
               && (columnContents.find('B') == std::string::npos)
               && (columnContents.find('C') == std::string::npos);

    default:
        break;
    }

    throw std::invalid_argument("Unknown letter");
}

/**
 * @brief Solve part 2 of puzzle
 *
 * @param doPrint print the solution steps
 * @return int Final solution
 */
static int Part2(bool doPrint)
{
    // #############
    // #01.3.5.7.9A#
    // ###2#4#6#8###
    //   #.#.#.#.#
    //   #.#.#.#.#
    //   #.#.#.#.#
    //   #########

    std::unordered_map<std::pair<int, int>, std::vector<int>> enroute{
        {{0, 2}, {1}},
        {{0, 4}, {1, 3}},
        {{0, 6}, {1, 3, 5}},
        {{0, 8}, {1, 3, 5, 7}},

        {{1, 2}, {}},
        {{1, 4}, {3}},
        {{1, 6}, {3, 5}},
        {{1, 8}, {3, 5, 7}},

        {{2, 3}, {}},
        {{3, 4}, {}},
        {{3, 6}, {5}},
        {{3, 8}, {5, 7}},

        {{2, 5}, {3}},
        {{4, 5}, {}},
        {{5, 6}, {}},
        {{5, 8}, {7}},

        {{2, 7}, {3, 5}},
        {{4, 7}, {5}},
        {{6, 7}, {}},
        {{7, 8}, {}},

        {{2, 9}, {3, 5, 7}},
        {{4, 9}, {5, 7}},
        {{6, 9}, {7}},
        {{8, 9}, {}},

        {{2, 10}, {3, 5, 7, 9}},
        {{4, 10}, {5, 7, 9}},
        {{6, 10}, {7, 9}},
        {{8, 10}, {9}},

        {{2, 4}, {3}},
        {{2, 6}, {3, 5}},
        {{2, 8}, {3, 5, 7}},

        {{4, 6}, {5}},
        {{4, 8}, {5, 7}},

        {{6, 8}, {7}},
    };

    // Pair of route and cost (steps)
    std::unordered_map<int, std::vector<std::pair<int, int>>> puzzleMap{
        {0, {{2, 3}, {4, 5}, {6, 7}, {8, 9}}},
        {1, {{2, 2}, {4, 4}, {6, 6}, {8, 8}}},
        {3, {{2, 2}, {4, 2}, {6, 4}, {8, 6}}},
        {5, {{2, 4}, {4, 2}, {6, 2}, {8, 4}}},
        {7, {{2, 6}, {4, 4}, {6, 2}, {8, 2}}},
        {9, {{2, 8}, {4, 6}, {6, 4}, {8, 2}}},
        {10, {{2, 9}, {4, 7}, {6, 5}, {8, 3}}},

        {2,
         {{0, 3},
          {1, 2},
          {3, 2},
          {4, 4},
          {5, 4},
          {6, 6},
          {7, 6},
          {8, 8},
          {9, 8},
          {10, 9}}},
        {4,
         {{0, 5},
          {1, 4},
          {2, 4},
          {3, 2},
          {5, 2},
          {6, 4},
          {7, 4},
          {8, 6},
          {9, 6},
          {10, 7}}},
        {6,
         {{0, 7},
          {1, 6},
          {2, 6},
          {3, 4},
          {4, 4},
          {5, 2},
          {7, 2},
          {8, 4},
          {9, 4},
          {10, 5}}},
        {8,
         {{0, 9},
          {1, 8},
          {2, 8},
          {3, 6},
          {4, 6},
          {5, 4},
          {6, 4},
          {7, 2},
          {9, 2},
          {10, 3}}},
    };

    PuzzleGrid start{"",     "", "BDDB", "", "CBCC", "",
                     "DABA", "", "ACAD", "", ""};
    PuzzleGrid end{"", "", "AAAA", "", "BBBB", "", "CCCC", "", "DDDD", "", ""};

    std::priority_queue<PriorityElement> frontier;
    frontier.push(std::make_pair(start, 0));
    std::unordered_set<PuzzleGrid> visited{start};
    std::unordered_map<PuzzleGrid, int> costs;
    std::unordered_map<PuzzleGrid, PuzzleGrid> cameFrom;

    costs[start] = 0;

    while (!frontier.empty())
    {
        auto [current, priority] = frontier.top();
        frontier.pop();

        if (current == end)
        {
            if (doPrint)
                PrintRoute(cameFrom, costs, current);
            return costs[current];
        }

        // Expand
        for (int fromIndex = 0; fromIndex < static_cast<int>(current.size());
             fromIndex++)
        {
            for (const auto& [toIndex, steps] : puzzleMap[fromIndex])
            {
                // If moving to out of bounds or from empty position
                if ((toIndex < 0)
                    || (toIndex >= static_cast<int>(current.size()))
                    || (current[fromIndex].length() == 0))
                    continue;

                // If moving to a column and it's full
                if (current[toIndex].length() == 4)
                    continue;

                bool movingToRoom
                    = std::count(columns.begin(), columns.end(), toIndex);
                bool movingFromRoom
                    = std::count(columns.begin(), columns.end(), fromIndex);

                // If moving to waiting area but it's full
                if (!(movingToRoom || (current[toIndex].length() == 0)))
                    continue;

                // If blocked path
                bool blockedPath = false;
                for (const auto& pointOnRoute :
                     enroute[std::make_pair(std::min(fromIndex, toIndex),
                                            std::max(fromIndex, toIndex))])
                    if (current[pointOnRoute].length())
                    {
                        blockedPath = true;
                        break;
                    }
                if (blockedPath)
                    continue;

                char letter = current[fromIndex][current[fromIndex].size() - 1];

                // If moving to a room, if it's not allowed, skip
                if (movingToRoom)
                    if (!IsColumnInsertionAllowed(letter, toIndex,
                                                  current[toIndex]))
                        continue;

                PuzzleGrid next;
                std::copy(current.begin(), current.end(), next.begin());

                next[toIndex].push_back(letter);
                if (!next[fromIndex].empty())
                    next[fromIndex].pop_back();

                if (visited.count(next))
                    continue;

                cameFrom[next] = current;

                int roomFromSteps = 0;
                int roomToSteps = 0;

                if (movingFromRoom)
                    roomFromSteps
                        = static_cast<int>(4 - current[fromIndex].length());

                if (movingToRoom)
                    roomToSteps
                        = static_cast<int>(3 - current[toIndex].length());

                costs[next]
                    = (cost[letter] * (steps + roomFromSteps + roomToSteps))
                      + costs[current];

                frontier.push(std::make_pair(next, costs[next]));
                visited.insert(next);
            }
        }
    }

    std::cout << "Oops, finished early!\n";

    return 0;
}

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
    std::cout << "Part 2: " << Part2(printMaps) << "\n";
}
