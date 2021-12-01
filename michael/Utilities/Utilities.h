#pragma once

#include <vector>

std::string ReadTextFile(const char *fileName);
std::vector<int> ReadNumbersFile(const char* fileName);
void PrintNumbers(const std::vector<int>& numbers);

template<typename T>
T Sum(const std::vector<T> numbers)
{
    T sum = 0;
    for (T number : numbers)
        sum += number;
    return sum;
}

