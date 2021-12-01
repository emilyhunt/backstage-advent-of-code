#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> ReadFile(const char *fileName);
int Part1(const std::vector<int> &numbers);
int Part2(const std::vector<int> &numbers);

std::vector<int> ReadFile(const char *fileName)
{
    int i;
    std::vector<int> numbers;
    std::ifstream file(fileName);

    while (file >> i)
        numbers.push_back(i);

    return numbers;
}

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
    std::vector<int> numbers = ReadFile("02/data/input.txt");
    std::cout << "Part 1: " << Part1(numbers) << "\n";
    std::cout << "Part 2: " << Part2(numbers) << "\n";

    return 0;
}
