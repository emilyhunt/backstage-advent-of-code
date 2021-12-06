#include <algorithm>
#include <iostream>
#include <vector>

#include "Utilities/Utilities.h"

/*
================================================================================
                            Function Declarations
================================================================================
*/

/*
================================================================================
                            Function Definitions
================================================================================
*/

void Decrement(std::vector<int>& lanternfish)
{
    for (auto& fish : lanternfish)
        fish--;
}

void SpawnLanternfish(std::vector<int>& lanternfish)
{
    std::size_t newFish = 0;
    for (auto& fish : lanternfish)
    {
        if (fish < 0)
        {
            fish = 6;
            newFish++;
        }
    }

    lanternfish.insert(lanternfish.end(), newFish, 8);
}

int Part1(std::vector<int>& lanternfish)
{
    for (int i = 0; i < 80; i++)
    {
        Decrement(lanternfish);
        SpawnLanternfish(lanternfish);
    }
    return lanternfish.size();
}

int main()
{
    std::vector<int> lanternfish = ReadNumbersFile("06/data/input.txt");

    std::cout << "Part 1: " << Part1(lanternfish) << "\n";

    return 0;
}
