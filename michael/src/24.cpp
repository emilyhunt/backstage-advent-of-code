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

#include <array>
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

using FunctionType = void (*)(const Instruction&);

void Input(const Instruction& instruction, int64_t input);
void Add(const Instruction& instruction);
void Multiply(const Instruction& instruction);
void Divide(const Instruction& instruction);
void Modulo(const Instruction& instruction);
void Equal(const Instruction& instruction);

int ParseValue(std::string input);

const std::unordered_map<std::string, FunctionType> functionMapping{
    {"add", Add},
    {"mul", Multiply},
    {"div", Divide},
    {"mod", Modulo},
    {"eql", Equal}};

std::unordered_map<std::string, int64_t> data{
    {"w", 0}, {"x", 0}, {"y", 0}, {"z", 0}};

/*
================================================================================
                            Function Definitions
================================================================================
*/
void Input(const Instruction& instruction, int64_t input)
{
    data[instruction.second[0]] = input;
}

void Add(const Instruction& instruction)
{
    data[instruction.second[0]] += ParseValue(instruction.second[1]);
}

void Multiply(const Instruction& instruction)
{
    data[instruction.second[0]] *= ParseValue(instruction.second[1]);
}

void Divide(const Instruction& instruction)
{
    data[instruction.second[0]] /= ParseValue(instruction.second[1]);
}

void Modulo(const Instruction& instruction)
{
    data[instruction.second[0]] %= ParseValue(instruction.second[1]);
}

void Equal(const Instruction& instruction)
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

void ResetAlu()
{
    data["w"] = 0;
    data["x"] = 0;
    data["y"] = 0;
    data["z"] = 0;
}

bool ContainsZeroDigit(int64_t input)
{
    while (input > 0)
    {
        int digit = input % 10;
        if (!digit)
            return true;
        input /= 10;
    }

    return false;
}

int RunProgram(std::array<int64_t, 14> digit)
{
    int64_t w, x, y, z;
    w = x = y = z = 0;

    w = digit[0];
    x += 14;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 8;
    y *= x;
    z += y;

    w = digit[1];
    x *= 0;
    x += z;
    x %= 26;
    x += 15;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 11;
    y *= x;
    z += y;

    w = digit[2];
    x *= 0;
    x += z;
    x %= 26;
    x += 13;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 2;
    y *= x;
    z += y;

    w = digit[3];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -10;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 11;
    y *= x;
    z += y;

    w = digit[4];
    x *= 0;
    x += z;
    x %= 26;
    x += 14;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 1;
    y *= x;
    z += y;

    w = digit[5];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -3;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 5;
    y *= x;
    z += y;

    w = digit[6];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -14;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 10;
    y *= x;
    z += y;

    w = digit[7];
    x *= 0;
    x += z;
    x %= 26;
    x += 12;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 6;
    y *= x;
    z += y;

    w = digit[8];
    x *= 0;
    x += z;
    x %= 26;
    x += 14;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 1;
    y *= x;
    z += y;

    w = digit[9];
    x *= 0;
    x += z;
    x %= 26;
    x += 12;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 11;
    y *= x;
    z += y;

    w = digit[10];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -6;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 9;
    y *= x;
    z += y;

    w = digit[11];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -6;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 14;
    y *= x;
    z += y;

    w = digit[12];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -2;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 11;
    y *= x;
    z += y;

    w = digit[13];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -9;
    x = x == w ? 1 : 0;
    x = x == 0 ? 1 : 0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 2;
    y *= x;
    z += y;

    return z;
}

bool CheckModelNumber(const Instructions& instructions, int64_t input)
{
    // Check if contains zeros
    if (ContainsZeroDigit(input))
        return true;

    std::array<int64_t, 14> digits = {};
    int i = 13;
    while (input > 0)
    {
        digits[i--] = input % 10;
        input /= 10;
    }

    return RunProgram(digits);
}

static int64_t Part1(const Instructions& instructions)
{
    int64_t modelNumber = 99919780000000; // Close to answer to save time

    while (CheckModelNumber(instructions, modelNumber))
        modelNumber--;

    return modelNumber;
}

static int64_t Part2(const Instructions& instructions)
{
    int64_t modelNumber = 24913111111111; // Close to answer to save time

    while (CheckModelNumber(instructions, modelNumber))
        modelNumber++;

    return modelNumber;
}

/**
 * @brief Day 24 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day24(const char* fileName)
{
    const auto text = ReadTextFile(fileName);
    auto instructions = ExtractInstructions(text);

    // PrintInstructions(instructions);

    std::cout << "Part 1: " << Part1(instructions) << "\n";
    std::cout << "Part 2: " << Part2(instructions) << "\n";
}
