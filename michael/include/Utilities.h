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

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#pragma once

std::string ReadTextFile(const char* fileName);
void PrintNumbers(const std::vector<int>& numbers, const char* sep);
std::vector<std::string> SplitLines(const std::string& text);
std::vector<std::string> Split(const std::string& text,
                               const std::string& delim);
std::vector<std::vector<int>> ParseTextToNumberGrid(const std::string& text);
void PrintNumberGrid(const std::vector<std::vector<int>>& numberGrid);
std::vector<int> ReadNumbers(const std::string& text);
std::vector<int> ReadNumbersFile(const char* fileName);

/**
 * @brief Timer object
 *
 * Intended for use on stack scope, timer starts when initialised, and timer
 * stops when destructed. Duration is then printed to std::cout.
 */
class Timer
{
private:
    /// Start time
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

    /**
     * @brief Stop the clock and find duration
     */
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
 * @brief Limit the value by the given minimum and maximum values
 *
 * @tparam T any numeric type
 * @param value to be limited
 * @param min value
 * @param max value
 * @return limited value
 */
template <typename T>
T Limit(T value, T min, T max)
{
    value = std::max(min, value);
    value = std::min(max, value);
    return value;
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

/**
 * @brief Find the median of a list of numbers
 *
 * @tparam T Type of input used
 * @param numbers The list of numbers
 * @return Median of list of numbers
 */
template <typename T>
T Median(std::vector<T> numbers)
{
    size_t n = numbers.size() / 2;
    std::nth_element(numbers.begin(), numbers.begin() + n, numbers.end());
    return numbers[n];
}

/**
 * @brief Find the meean of a list of numbers
 *
 * @tparam T Type of input used
 * @param numbers The list of numbers
 * @return Mean of list of numbers
 */
template <typename T>
T Mean(std::vector<T> numbers)
{
    return std::reduce(numbers.begin(), numbers.end())
           / static_cast<T>(numbers.size());
}
