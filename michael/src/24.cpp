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

using FunctionType = void (*)(Instruction);

void Input(Instruction instruction);
void Add(Instruction instruction);
void Multiply(Instruction instruction);
void Divide(Instruction instruction);
void Modulo(Instruction instruction);
void Equal(Instruction instruction);

int ParseValue(std::string input);

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
void Input(Instruction instruction) { return; }

void Add(Instruction instruction)
{
    data[instruction.second[0]] += ParseValue(instruction.second[1]);
}

void Multiply(Instruction instruction)
{
    data[instruction.second[0]] *= ParseValue(instruction.second[1]);
}

void Divide(Instruction instruction)
{
    data[instruction.second[0]] /= ParseValue(instruction.second[1]);
}

void Modulo(Instruction instruction)
{
    data[instruction.second[0]] %= ParseValue(instruction.second[1]);
}

void Equal(Instruction instruction)
{
    bool truthVal = ParseValue(instruction.second[0])
                    == ParseValue(instruction.second[1]);
    data[instruction.second[0]] = truthVal ? 1 : 0;
}

int ParseValue(std::string input)
{
    if (input[0] >= 'a')
        return data.at(input);

    return std::stoi(input);
}

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
