/**
 * @file 16.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 16
 * @version 1.0.0
 * @date 2021-12-16
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <map>
#include <string>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Classes
================================================================================
*/
enum class State
{
    version,
    typeId,
    lengthId,
    data,
    totalLength,
    numOfSubPackets,
    end,
};

/*
================================================================================
                            Function Definitions
================================================================================
*/
std::string HexCharToBin(char ch)
{
    std::map<char, std::string> map
        = {{'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
           {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
           {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
           {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};
    return map[ch];
}

std::string GetBinData(const std::string& hex)
{
    std::string bin;
    for (const auto& ch : hex)
        bin += HexCharToBin(ch);
    return bin;
}

int Part1(const std::string& bin, int& index)
{
    std::cout << bin << "\n";
    int answer = 0;
    State currentState = State::version;

    while (index < bin.size())
    {
        switch (currentState)
        {
        case State::version:
        {
            const int len = 3;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;
            std::cout << "Version: " << total << "\n";
            currentState = State::typeId;
            answer += total;
        }
        break;

        case State::typeId:
        {
            const int len = 3;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;

            std::cout << "Type ID: " << total << "\n";

            if (total == 4)
                currentState = State::data;
            else
                currentState = State::lengthId;
        }
        break;

        case State::lengthId:
        {
            int a = bin[index++] - '0';
            if (a)
                currentState = State::numOfSubPackets;
            else
                currentState = State::totalLength;
            std::cout << "Length ID: " << a << "\n";
        }
        break;

        case State::totalLength:
        {
            const int len = 15;
            int total = 0;

            const int highNum = -1;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;
            std::cout << "Total Length: " << total << "\n";
            const int start = index;
            while ((index - start) < total)
            {
                answer += Part1(bin, index);
            }
            currentState = State::end;
        }
        break;

        case State::numOfSubPackets:
        {
            const int len = 11;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;
            std::cout << "Num of sub-packets: " << total << "\n";

            for (int i = 0; i < total; i++)
            {
                answer += Part1(bin, index);
            }
            currentState = State::version;
        }
        break;

        case State::data:
        {
            bool run = true;
            const int len = 5;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;
            currentState = (total & 0x10) ? State::data : State::end;
            std::cout << "Data: " << total << "\n";
        }
        break;

        case State::end:
        default:
            return answer;
            break;
        }
    }

    std::cout << "<=====\n";
    return answer;
}

/**
 * @brief Day 16 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day16(const char* fileName)
{
    const std::string hex = ReadTextFile(fileName);
    auto bin = GetBinData(hex);
    int index = 0;
    std::cout << "Part 1:\n\n" << Part1(bin, index) << "\n";
}
