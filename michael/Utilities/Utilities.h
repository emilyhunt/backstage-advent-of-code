#include <regex>
#include <string>
#include <vector>

#pragma once

std::string ReadTextFile(const char* fileName);
void PrintNumbers(const std::vector<int>& numbers);

template <typename T>
T Sum(const std::vector<T> numbers)
{
    T sum = 0;
    for (T number : numbers)
        sum += number;
    return sum;
}

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
