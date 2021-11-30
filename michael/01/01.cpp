#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<int> ReadFile(const char *fileName)
{
    int i;
    std::vector<int> numbers;
    std::ifstream file(fileName);

    while (file >> i)
        numbers.push_back(i);

    return numbers;
}

void PrintNumbers(const std::vector<int>& numbers)
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

int main()
{
    std::vector<int> numbers = ReadFile("01/data/input.txt");
    PrintNumbers(numbers);

    return 0;
}
