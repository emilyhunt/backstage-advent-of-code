#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> ReadFile(const char *fileName);
void PrintNumbers(const std::vector<int> &numbers);
int Sum(const std::vector<int> &numbers);
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
    int sum = 0;
    for (size_t i = 0; i < numbers.size() - 1; i++)
    {
        if ((numbers[i + 1] - numbers[i]) > 0)
            sum += 1;
    }
    return sum;
}

int Part2(const std::vector<int> &numbers)
{
    std::vector<int> windowed;
    for (size_t i = 0; i < numbers.size() - 2; i++)
        windowed.push_back(numbers[i] + numbers[i + 1] + numbers[i + 2]);

    return Part1(windowed);
}

int main()
{
    std::vector<int> numbers = ReadFile("01/data/input.txt");
    std::cout << "Part 1: " << Part1(numbers) << "\n";
    std::cout << "Part 2: " << Part2(numbers) << "\n";

    return 0;
}
