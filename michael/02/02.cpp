#include <iostream>
#include <vector>

#include "Utilities/Utilities.h"

int Part1(const std::vector<int> &numbers);
int Part2(const std::vector<int> &numbers);

int Part1(const std::vector<int> &numbers)
{
    return 0;
}

int Part2(const std::vector<int> &numbers)
{
    return 0;
}

int main()
{
    std::vector<int> numbers = ReadNumbersFile("02/data/input.txt");
    
    std::cout << "Part 1: " << Part1(numbers) << "\n";
    std::cout << "Part 2: " << Part2(numbers) << "\n";

    return 0;
}
