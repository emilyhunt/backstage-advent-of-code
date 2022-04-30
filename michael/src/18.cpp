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

#include <algorithm>
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

static bool debugMode = false;

/// Pair is value, depth
class Row
{
private:
    std::vector<std::pair<int, int>> m_valueDepthPair;

    void Explode(std::size_t idx, int depth, int value)
    {
        if (debugMode)
            std::cout << "Explode(" << value << "," << depth << ")[" << idx
                      << "]\n"
                      << *this << "\n";

        if (idx != 0)
            m_valueDepthPair[idx - 1].first += value;

        if (idx < m_valueDepthPair.size() - 2)
            m_valueDepthPair[idx + 2].first += m_valueDepthPair[idx + 1].first;

        m_valueDepthPair.erase(m_valueDepthPair.begin() + idx,
                               m_valueDepthPair.begin() + idx + 2);
        m_valueDepthPair.insert(m_valueDepthPair.begin() + idx,
                                std::make_pair(0, depth - 1));

        if (debugMode)
            std::cout << *this << "\n\n";
    }

    void Split(std::size_t idx, int depth, double fValue)
    {
        if (debugMode)
            std::cout << "Split(" << fValue << "," << depth << ")[" << idx
                      << "]\n"
                      << *this << "\n";
        m_valueDepthPair.erase(m_valueDepthPair.begin() + idx);
        m_valueDepthPair.insert(
            m_valueDepthPair.begin() + idx,
            {{static_cast<int>(std::floor(fValue / 2.0)), depth + 1},
             {static_cast<int>(std::ceil(fValue / 2.0)), depth + 1}});
        if (debugMode)
            std::cout << *this << "\n\n";
    }

    int GetMaxDepth() const
    {
        int level = 0;
        for (const auto& [_, depth] : m_valueDepthPair)
            return std::max(level, depth);
        return level;
    }

    bool ReduceStep()
    {
        for (std::size_t idx = 0; idx < m_valueDepthPair.size(); idx++)
        {
            auto [value, depth] = m_valueDepthPair[idx];
            if (depth > 4)
            {
                Explode(idx, depth, value);
                return true;
            }
        }

        for (std::size_t idx = 0; idx < m_valueDepthPair.size(); idx++)
        {
            auto [value, depth] = m_valueDepthPair[idx];
            if (value >= 10)
            {
                Split(idx, depth, value);
                return true;
            }
        }
        return false;
    }

public:
    Row(const std::string& line)
    {
        int depth = 0;

        for (auto ch : line)
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
                m_valueDepthPair.push_back(std::make_pair(ch - '0', depth));
                break;
            }
        }
    }

    void Reduce()
    {
        while (ReduceStep())
        {
        }
    }

    int GetMagnitude() const
    {
        if (!this->m_valueDepthPair.size())
            return 0;
        int level = this->GetMaxDepth();
        Row row = *this;

        for (std::size_t i = level; i >= 1; i--)
        {
            bool didMerge;
            do
            {
                didMerge = false;
                for (std::size_t j = 0; j < row.m_valueDepthPair.size() - 1;
                     j++)
                {
                    if (row.m_valueDepthPair[j].second == static_cast<int>(i))
                    {
                        auto pair = std::make_pair(
                            3 * row.m_valueDepthPair[j].first
                                + 2 * row.m_valueDepthPair[j + 1].first,
                            i - 1);
                        row.m_valueDepthPair.erase(
                            row.m_valueDepthPair.begin() + j,
                            row.m_valueDepthPair.begin() + j + 2);
                        if (j >= row.m_valueDepthPair.size())
                            row.m_valueDepthPair.insert(
                                row.m_valueDepthPair.end(), pair);
                        else
                            row.m_valueDepthPair.insert(
                                row.m_valueDepthPair.begin() + j, pair);
                        didMerge = true;
                        break;
                    }
                }
            } while (didMerge);
            if (row.m_valueDepthPair.size() == 2)
                break;
        }

        return row.m_valueDepthPair[0].first * 3
               + row.m_valueDepthPair[1].first * 2;
    }

    Row operator+(const Row& other) const
    {
        Row newRow = *this;

        newRow.m_valueDepthPair.insert(newRow.m_valueDepthPair.end(),
                                       other.m_valueDepthPair.begin(),
                                       other.m_valueDepthPair.end());

        for (auto& elem : newRow.m_valueDepthPair)
            elem.second++;

        newRow.Reduce();
        return newRow;
    }

    Row& operator+=(const Row& other)
    {
        this->m_valueDepthPair.insert(this->m_valueDepthPair.end(),
                                      other.m_valueDepthPair.begin(),
                                      other.m_valueDepthPair.end());
        for (auto& elem : this->m_valueDepthPair)
            elem.second++;
        this->Reduce();

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Row& row);
};

std::ostream& operator<<(std::ostream& os, const Row& row)
{
    for (const auto& elem : row.m_valueDepthPair)
        os << "(" << elem.first << "," << elem.second << ")";
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

        while ((lineEnd = text.find('\n', lineStart)) != std::string::npos)
        {
            std::string line
                = text.substr(lineStart, (lineEnd - 1) - lineStart);
            m_rows.push_back(line);
            lineStart = lineEnd + 1;
        }

        std::string line = text.substr(lineStart);
        m_rows.push_back(Row(line));
    }

    Row FindTotalSum() const
    {
        Snailfish rows(*this);

        while (rows.m_rows.size() > 1)
        {
            rows.m_rows[0] += rows.m_rows[1];
            rows.m_rows.erase(rows.m_rows.begin() + 1, rows.m_rows.begin() + 2);
            // rows.m_rows[0].Reduce();
        }
        // rows.m_rows[0].Reduce();

        return rows.m_rows[0];
    }

    std::vector<int> FindAllSumCombinations() const
    {
        std::vector<int> sums;

        for (std::size_t i = 0; i < m_rows.size(); i++)
        {
            for (std::size_t j = 0; j < m_rows.size(); j++)
            {
                if (i == j)
                    continue;

                Row summedRow = m_rows[i] + m_rows[j];
                summedRow.Reduce();
                auto num = summedRow.GetMagnitude();
                sums.push_back(num);
            }
        }

        return sums;
    }

    /**
     * @brief Get the magnitude of the first row. Should be the only row after
     * sum
     *
     * @return int the magnitude
     */
    int GetMagnitude(std::size_t index) const
    {
        return m_rows[index].GetMagnitude();
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
    auto sums = snailfish.FindAllSumCombinations();
    auto totalSum = snailfish.FindTotalSum();
    std::cout << "Part 1: " << totalSum.GetMagnitude() << "\n";
    std::cout << "Part 2: " << *std::max_element(sums.begin(), sums.end())
              << "\n";
}
