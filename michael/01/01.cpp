#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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

int Part1(const std::vector<int> &numbers)
{
    std::vector<int> diffs;
    for (int i = 0; i < numbers.size() - 1; i++)
    {
        if ((numbers[i + 1] - numbers[i]) > 0)
            diffs.push_back(1);
    }
    return Sum(diffs);
}

int Sum(const std::vector<int> &numbers)
{
    int sum = 0;
    for (int i : numbers)
        sum += i;
    return sum;
}

int main()
{
    std::vector<int> numbers = ReadFile("01/data/input.txt");
    std::cout << Part1(numbers) << std::endl;

    return 0;
}
