#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "Utilities/Utilities.h"

std::string ReadTextFile(const char* fileName)
{
    std::ifstream file(fileName);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<int> ReadNumbersFile(const char* fileName)
{
    std::vector<int> numbers;
    std::string text = ReadTextFile(fileName);
    std::regex numberRegex("\\d+");

    auto begin = std::sregex_iterator(text.begin(), text.end(), numberRegex);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator iter = begin; iter != end; iter++)
        numbers.push_back(std::atoi((*iter).str().c_str()));

    return numbers;
}

void PrintNumbers(const std::vector<int>& numbers)
{
    std::ostream_iterator<int> iter(std::cout, " ");
    std::copy(numbers.begin(), numbers.end(), iter);
    std::cout << std::endl;
}
