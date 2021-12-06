/**
 * @file 02.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 2
 * @version 1.0.0
 * @date 2021-12-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "Utilities/Utilities.h"

int Part1(const std::vector<std::tuple<std::string, int>> &instructions);
int Part2(const std::vector<std::tuple<std::string, int>> &instructions);
std::vector<std::tuple<std::string, int>> ExtractInstructions(const std::string &text);

int Part1(const std::vector<std::tuple<std::string, int>> &instructions)
{
    int coords[2] = {0, 0};
    for (auto &instruction : instructions)
    {
        auto &[direction, amount] = instruction;
        if (direction == "forward")
            coords[0] += amount;
        else if (direction == "down")
            coords[1] += amount;
        else if (direction == "up")
            coords[1] -= amount;
        else
            std::cerr << "'" << direction << "' is not allowed" << std::endl;
    }

    return coords[0] * coords[1];
}

int Part2(const std::vector<std::tuple<std::string, int>> &instructions)
{
    int aim = 0;
    int coords[2] = {0, 0};
    for (auto &instruction : instructions)
    {
        auto &[direction, amount] = instruction;
        if (direction == "forward")
        {
            coords[0] += amount;
            coords[1] += aim * amount;
        }
        else if (direction == "down")
            aim += amount;
        else if (direction == "up")
            aim -= amount;
        else
            std::cerr << "'" << direction << "' is not allowed" << std::endl;
    }

    return coords[0] * coords[1];
}

std::vector<std::tuple<std::string, int>> ExtractInstructions(const std::string &text)
{
    std::stringstream textStream(text);
    std::vector<std::tuple<std::string, int>> instructions;

    while (textStream)
    {
        std::string instruction;
        int amount;
        if (!(textStream >> instruction))
            break;
        textStream >> amount;
        auto line = std::make_tuple(instruction, amount);
        instructions.push_back(line);
    }
    return instructions;
}

int main()
{
    std::string text = ReadTextFile("02/data/input.txt");
    auto instructions = ExtractInstructions(text);

    std::cout << "Part 1: " << Part1(instructions) << "\n";
    std::cout << "Part 2: " << Part2(instructions) << "\n";

    return 0;
}
