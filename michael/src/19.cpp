/**
 * @file 19.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 19
 * @version 1.0.0
 * @date 2021-12-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <string>
#include <regex>
#include <array>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                            Function Definitions
================================================================================
*/

std::vector<std::vector<std::array<int, 3>>> CreateScannerData(const std::string &text)
{
    std::regex scannerRegex("--- scanner \\d+ ---\n((?:-*\\d+,){2}-*\\d+\\n*)+");
    std::regex coordRegex("(-*\\d+),(-*\\d+),(-*\\d+)");
    std::smatch scannerMatch, coordMatch;

    auto beginScanner = std::sregex_iterator(text.begin(), text.end(), scannerRegex);
    auto end = std::sregex_iterator();

    std::vector<std::vector<std::array<int, 3>>> scanners;

    int scannerId = 0;
    for (auto i = beginScanner; i != end; i++)
    {
        scannerMatch = *i;
        scanners.push_back(std::vector<std::array<int, 3>>());
        auto coordsStr = scannerMatch.str();
        auto beginCoord = std::sregex_iterator(coordsStr.begin(), coordsStr.end(), coordRegex);
        // std::cout << "Scanner: " << scannerId << std::endl;
        for (auto j = beginCoord; j != end; j++)
        {
            coordMatch = *j;
            // std::cout << coordMatch.str() << std::endl;
            auto coord = std::array<int, 3>{std::stoi(coordMatch[1].str()), std::stoi(coordMatch[2].str()), std::stoi(coordMatch[3].str())};
            scanners[scannerId].push_back(coord);
        }

        scannerId++;
    }
    return scanners;
}

void PrintScannerData(const std::vector<std::vector<std::array<int, 3>>>& scanners)
{
    int scannerId = 0;
    for (const auto& scanner: scanners)
    {
        std::cout << "\nScanner: " << scannerId++ << "\n";
        for (const auto& coord : scanner)
        {
            for (const auto& axis : coord)
            {
                std::cout << axis << ", ";
            }
            std::cout << "\n";
        }
    }
}


/**
 * @brief Day 19 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day19(const char *fileName)
{
    const std::string text = ReadTextFile(fileName);
    auto scannerData = CreateScannerData(text);
    PrintScannerData(scannerData);
}
