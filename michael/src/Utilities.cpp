/**
 * @file Utilities.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 general utility source
 * @version 1.0.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <exception>
#include <fstream>
#include <sstream>

#include "Utilities.h"

/**
 * @brief Read file to a string
 *
 * @param fileName Path to file to read
 * @return std::string Text from file copied to string
 */
std::string ReadTextFile(const char* fileName)
{
    std::ifstream file(fileName);
    if (!file)
        throw std::invalid_argument(fileName);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief Print a vector of ints
 *
 * @param numbers Vector of numbers to print
 * @param sep Seperator between values when printed
 */
void PrintNumbers(const std::vector<int>& numbers, const char* sep = " ")
{
    PrintVector<int>(numbers, sep);
}

/**
 * @brief Split lines
 * 
 * @param text String to split
 * @return std::vector<std::string> Split into vector of strings
 */
std::vector<std::string> SplitLines(const std::string& text)
{
    return Split(text, "\n");
}

/**
 * @brief Split a string by a delimiter
 * 
 * @param text The string to split
 * @param delim Delimiter
 * @return std::vector<std::string> Split into vector of strings
 */
std::vector<std::string> Split(const std::string& text,
                               const std::string& delim)
{
    std::vector<std::string> splitString;
    size_t last = 0;
    size_t next = 0;
    while ((next = text.find(delim, last)) != std::string::npos)
    {
        splitString.push_back(text.substr(last, next - last));
        last = next + 1;
    }
    splitString.push_back(text.substr(text.rfind("\n") + 1, text.length()));
    return splitString;
}
