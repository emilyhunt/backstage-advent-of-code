/**
 * @file Utilities.h
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 general utility headers
 * @version 1.0.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <unordered_map>

#pragma once

std::string ReadTextFile(const char* fileName);
void PrintNumbers(const std::vector<int>& numbers, const char* sep);
std::vector<std::string> SplitLines(const std::string& text);
std::vector<std::string> Split(const std::string& text,
                               const std::string& delim);
std::vector<std::vector<int>> ParseTextToNumberGrid(const std::string& text);
void PrintNumberGrid(const std::vector<std::vector<int>>& numberGrid);

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    void Stop()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                            end - m_start)
                            .count();
        double msDuration = duration * 0.001;
        std::cout << "Time: " << msDuration << "ms\n";
    }

public:
    Timer() { m_start = std::chrono::high_resolution_clock::now(); }
    ~Timer() { Stop(); }
};

/**
 * @brief Read numbers to a vector of numbers, can be spaced by anything
 *
 * @tparam T data will be read as this integer type
 * @param fileName Path to file to read from
 * @return std::vector<T> Vector of integer type
 */
template <typename T>
std::vector<T> ReadNumbersFile(const char* fileName)
{
    std::vector<T> numbers;
    std::string text = ReadTextFile(fileName);
    std::regex numberRegex("\\d+");

    auto begin = std::sregex_iterator(text.begin(), text.end(), numberRegex);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator iter = begin; iter != end; iter++)
        numbers.push_back(std::atoi((*iter).str().c_str()));

    return numbers;
}

/**
 * @brief Prints all elements of a vector
 *
 * @tparam T any ostream compatible type
 * @param vec vector of printable elements
 * @param sep Seperator between elements
 */
template <typename T>
void PrintVector(const T& vec, const char* sep = " ")
{
    for (const auto& item : vec)
        std::cout << item << sep;
    std::cout << "\n";
}

/**
 * @brief Print a map like a python dict
 *
 * @tparam T1 unordered_map key type
 * @tparam T2 unordered_map val type
 * @param map The map to print
 * @param keyValSep Optional seperator between keys and values. Default is ": "
 * @param elemSep Optional seperator between each key value pair. Default is ",
 * "
 */
template <typename T1, typename T2>
void PrintMap(const std::unordered_map<T1, T2>& map,
              const char* keyValSep = ": ", const char* elemSep = ", ")
{
    std::cout << "{";
    bool isFirst = true;
    for (const auto& [key, val] : map)
    {
        if (isFirst)
        {
            std::cout << key << keyValSep << val;
            isFirst = false;
        }
        else
            std::cout << elemSep << key << keyValSep << val;
    }
    std::cout << "}\n";
}

/**
 * @brief Generic sign function, returns +1, 0 or -1
 *
 * @tparam T Type of input used
 * @param val to find sign of
 * @return int +1 for positive sign, -1 for negative sign, otherwise 0
 */
template <typename T>
int Sign(T val)
{
    return (T(0) < val) - (val < T(0));
}
