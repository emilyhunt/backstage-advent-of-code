/**
 * @file 18.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 18
 * @version 1.0.0
 * @date 2021-12-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Classes
================================================================================
*/

/// Pair is value, depth
using Row = std::vector<std::pair<int, int>>;

std::ostream& operator<<(std::ostream& os, const Row& row)
{
    for (const auto& elem : row)
        os << "(" << elem.first << "," << elem.second << ")";
    os << "\n";
    return os;
}

class Snailfish
{
private:
    std::vector<Row> m_rows;

public:
    Snailfish(const std::string& text)
    {
        std::size_t lineStart = 0;
        std::size_t lineEnd;
        std::size_t lineIdx = 0;

        while ((lineEnd = text.find('\n', lineStart)) != std::string::npos)
        {
            m_rows.push_back(Row());

            std::string line
                = text.substr(lineStart, (lineEnd - 1) - lineStart);
            int depth = 0;

            for (const auto& ch : line)
            {
                switch (ch)
                {
                case '[':
                    depth++;
                    break;

                case ']':
                    depth--;
                    break;

                case ',':
                    break;

                default:
                    m_rows[lineIdx].push_back(std::make_pair(ch - '0', depth));
                    break;
                }
            }

            lineStart = lineEnd + 1;
            lineIdx++;
        }

        m_rows.push_back(Row());

        std::string line = text.substr(lineStart);
        int depth = 0;

        for (const auto& ch : line)
        {
            switch (ch)
            {
            case '[':
                depth++;
                break;

            case ']':
                depth--;
                break;

            case ',':
                break;

            default:
                m_rows[lineIdx].push_back(std::make_pair(ch - '0', depth));
                break;
            }
        }
    }

    void Reduce()
    {
        bool didReduce;
        do
        {
            didReduce = false;
            for (auto& row : m_rows)
            {
                std::size_t idx = 0;
                for (auto& [value, depth] : row)
                {
                    if (depth > 4)
                    {
                        // Explode
                        if (idx != 0)
                            row[idx - 1].first += value;

                        if (idx != row.size() - 1)
                            row[idx + 2].first += row[idx + 1].first;

                        row.erase(row.begin() + idx, row.begin() + idx + 2);
                        row.insert(row.begin() + idx,
                                   std::make_pair(0, depth - 1));

                        didReduce = true;
                        break;
                    }
                    idx++;
                }
                if (didReduce)
                    break;
            }

            if (didReduce)
                continue;

            for (auto& row : m_rows)
            {
                std::size_t idx = 0;
                for (auto& [value, depth] : row)
                {
                    if (value >= 10)
                    {
                        // Split
                        std::cout << "\n" << row;
                        double fValue = value;
                        row.erase(row.begin() + idx);
                        row.insert(row.begin() + idx,
                                   {{static_cast<int>(std::floor(fValue / 2.0)),
                                     depth + 1},
                                    {static_cast<int>(std::ceil(fValue / 2.0)),
                                     depth + 1}});
                        std::cout << row;

                        didReduce = true;
                        break;
                    }
                }
                if (didReduce)
                    break;
                idx++;
            }
        } while (didReduce);
    }

    void FindSum()
    {
        while (m_rows.size() > 1)
        {
            Row newRow = m_rows[0];
            newRow.insert(newRow.end(), m_rows[1].begin(), m_rows[1].end());

            for (auto& elem : newRow)
                elem.second++;

            m_rows.erase(m_rows.begin(), m_rows.begin() + 2);
            m_rows.insert(m_rows.begin(), newRow);
            Reduce();
        }
    }

    /**
     * @brief Get the magnitude of the first row. Should be the only row after
     * sum
     *
     * @return int the magnitude
     */
    int GetMagnitude() const
    {
        int level = 0;
        auto row = m_rows.front();
        for (const auto& [_, depth] : row)
            level = std::max(level, depth);

        for (std::size_t i = level; i >= 1; i--)
        {
            bool didMerge;
            do
            {
                didMerge = false;
                for (std::size_t j = 0; j < row.size(); j++)
                {
                    if (row[j].second == static_cast<int>(i))
                    {
                        auto pair = std::make_pair(
                            3 * row[j].first + 2 * row[j + 1].first, i - 1);
                        row.erase(row.begin() + j, row.begin() + j + 2);
                        row.insert(row.begin() + j, pair);
                        didMerge = true;
                        break;
                    }
                }
            } while (didMerge);
            if (row.size() == 2)
                break;
        }

        return row[0].first * 3 + row[1].first * 2;
    }

    friend std::ostream& operator<<(std::ostream& os, const Snailfish& fish);
};

std::ostream& operator<<(std::ostream& os, const Snailfish& fish)
{
    for (const auto& row : fish.m_rows)
    {
        os << row;
    }
    return os;
}

/*
================================================================================
                            Function Definitions
================================================================================
*/

/**
 * @brief Day 18 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day18(const char* fileName)
{
    Snailfish snailfish(ReadTextFile(fileName));
    std::cout << snailfish;
    snailfish.FindSum();
    std::cout << snailfish.GetMagnitude() << "\n";
}
