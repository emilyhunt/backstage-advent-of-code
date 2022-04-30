/**
 * @file 20.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 20
 * @version 1.0.0
 * @date 2021-12-20
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <string>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Classes
================================================================================
*/
/**
 * @brief Trench map image and enchancement algoritm
 *
 */
class TrenchMap
{
private:
    std::string m_algoritm;
    std::vector<std::string> m_image;

    std::size_t GetIndex(std::size_t row, std::size_t col) const
    {
        std::size_t index = 0;

        for (std::size_t i = row; i < (row + 3); i++)
        {
            for (std::size_t j = col; j < (col + 3); j++)
            {
                index <<= 1;
                index += m_image[i][j] == '#';
            }
        }

        return index;
    }

    void PushNBack(const std::string& line, std::size_t n)
    {
        for (std::size_t i = 0; i < n; i++)
            m_image.push_back(line);
    }

    void EnhanceStep()
    {
        const std::size_t sizeChange = 2;
        char gutterChar = (m_image[0][0] == '#')
                              ? m_algoritm[m_algoritm.length() - 1]
                              : m_algoritm[0];
        std::vector<std::string> newImage(
            m_image.size() + sizeChange,
            std::string(m_image[0].length() + sizeChange, gutterChar));

        for (std::size_t i = 0; i < (m_image.size() - sizeChange); i++)
        {
            for (std::size_t j = 0; j < (m_image[0].length() - sizeChange); j++)
            {
                std::size_t idx = GetIndex(i, j);
                newImage[i + 2].replace(j + 2, 1, 1, m_algoritm[idx]);
            }
        }

        m_image = std::move(newImage);
    }

public:
    TrenchMap(const std::string& text)
    {
        const std::size_t gutterSize = 3;
        std::size_t splitPoint = text.find("\n\n");
        std::size_t end;

        m_algoritm = text.substr(0, splitPoint);
        splitPoint += 1;

        std::size_t lineLen = text.find('\n', splitPoint + 1) - splitPoint
                              + (gutterSize * 2) - 1;

        std::string firstLine(lineLen, '.');

        PushNBack(firstLine, gutterSize);

        while ((end = text.find('\n', splitPoint + 1)) != std::string::npos)
        {
            m_image.push_back(
                "..." + text.substr(splitPoint + 1, end - splitPoint - 1)
                + "...");
            splitPoint = end;
        }
        m_image.push_back("..." + text.substr(splitPoint + 1) + "...");

        PushNBack(firstLine, gutterSize);
    }

    void Enhance(std::size_t n)
    {
        for (std::size_t i = 0; i < n; i++)
            EnhanceStep();
    }

    /**
     * @brief Count number of light pixels that are on
     *
     * @return int Number of light pixels
     */
    int64_t CountLightPixels() const
    {
        int64_t count = 0;
        for (const auto& row : m_image)
            count += std::count(row.begin(), row.end(), '#');

        return count;
    }

    friend std::ostream& operator<<(std::ostream& os, const TrenchMap& map);
};

/**
 * @brief Print to ostream
 *
 * @param os ostream to print to
 * @param map to print
 * @return std::ostream& reference to modified ostream
 */
std::ostream& operator<<(std::ostream& os, const TrenchMap& map)
{
    os << map.m_algoritm << "\n\n";
    for (const auto& row : map.m_image)
        os << row << "\n";
    return os;
}

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Day 20 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day20(const char* fileName)
{
    TrenchMap trenchMap(ReadTextFile(fileName));
    trenchMap.Enhance(2);
    std::cout << "Part 1: " << trenchMap.CountLightPixels() << "\n";
    trenchMap.Enhance(50 - 2);
    std::cout << "Part 2: " << trenchMap.CountLightPixels() << "\n";
}
