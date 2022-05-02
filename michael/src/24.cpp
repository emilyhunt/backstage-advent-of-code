/**
 * @file 24.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 24
 * @version 1.0.0
 * @date 2021-12-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Declarations
================================================================================
*/
using Instruction = std::pair<std::string, std::vector<std::string>>;
using Instructions = std::vector<Instruction>;

using FunctionType = int (*)(Instruction);

int Input(Instruction);
int Add(Instruction);
int Multiply(Instruction);
int Divide(Instruction);
int Modulo(Instruction);
int Equal(Instruction);

const std::unordered_map<std::string, FunctionType> functionMapping{
    {"inp", Input},  {"add", Add},    {"mul", Multiply},
    {"div", Divide}, {"mod", Modulo}, {"eql", Equal}};

std::unordered_map<std::string, int> data{
    {"w", 0}, {"x", 0}, {"y", 0}, {"z", 0}};

/*
================================================================================
                            Function Definitions
================================================================================
*/
int Input(Instruction) { return 0; }
int Add(Instruction) { return 0; }
int Multiply(Instruction) { return 0; }
int Divide(Instruction) { return 0; }
int Modulo(Instruction) { return 0; }
int Equal(Instruction) { return 0; }

static Instructions ExtractInstructions(const std::string& text)
{
    Instructions instructions;
    auto lines = SplitLines(text);

    for (const auto& line : lines)
    {
        auto left = line.substr(0, 3);
        auto right = Split(line.substr(4), " ");

        instructions.push_back(std::make_pair(left, right));
    }

    return instructions;
}

static void PrintInstructions(const Instructions& instructions)
{
    for (const auto& instruction : instructions)
    {
        std::cout << instruction.first << " ";
        for (const auto& item : instruction.second)
            std::cout << item << " ";
        std::cout << "\n";
    }
}

static int Part1(const Instructions& instructions) { return 0; }

/**
 * @brief Day 24 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day24(const char* fileName)
{
    const auto text = ReadTextFile(fileName);
    auto instructions = ExtractInstructions(text);

    PrintInstructions(instructions);

    std::cout << "Part 1: " << Part1(instructions) << "\n";
}
