#include <iostream>
#include <numeric>
#include <vector>

#include "Utilities/Utilities.h"

int Part1(const std::vector<int> &numbers);
int Part2(const std::vector<int> &numbers);

int Part1(const std::vector<int> &numbers)
{
    std::vector<int> diff(numbers.size(), 0);
    std::adjacent_difference(numbers.begin(), numbers.end(), diff.begin());

    int sum = 0;
    // Drop first adj diff as it is just the first number again
    for (auto iter = diff.begin() + 1; iter != diff.end(); iter++)
        if (*iter > 0)
            sum += 1;
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
    std::vector<int> numbers = ReadNumbersFile<int>("01/data/input.txt");
    std::cout << "Part 1: " << Part1(numbers) << "\n";
    std::cout << "Part 2: " << Part2(numbers) << "\n";

    return 0;
}
