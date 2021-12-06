#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Utilities/Utilities.h"

std::string ReadTextFile(const char* fileName)
{
    std::ifstream file(fileName);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void PrintNumbers(const std::vector<int>& numbers)
{
    std::ostream_iterator<int> iter(std::cout, " ");
    std::copy(numbers.begin(), numbers.end(), iter);
    std::cout << std::endl;
}
