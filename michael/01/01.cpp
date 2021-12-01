#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> ReadFile(const char *fileName);
void PrintNumbers(const std::vector<int> &numbers);
int Part1(const std::vector<int> &numbers);
int Sum(const std::vector<int> &numbers);


std::vector<int> ReadFile(const char *fileName)
{
    int i;
    std::vector<int> numbers;
    std::ifstream file(fileName);

    while (file >> i)
        numbers.push_back(i);

    return numbers;
}

void PrintNumbers(const std::vector<int> &numbers)
{
    bool first = true;
    for (int number : numbers)
    {
        if (first)
            first = false;
        else
            std::cout << ", ";

        std::cout << number;
    }
    std::cout << "\n";
}

int Sum(const std::vector<int> &numbers)
{
    int sum = 0;
    for (int i : numbers)
        sum += i;
    return sum;
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

int main()
{
    std::vector<int> numbers = ReadFile("01/data/input.txt");
    std::cout << "Part 1: " << Part1(numbers) << "\n";

    return 0;
}
