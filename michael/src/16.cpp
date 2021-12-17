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

int Part1(const std::string& bin, int subPackets)
{
    std::cout << bin << "\n";
    int answer = 0;
    State currentState = State::version;
    int i = 0;
    while (i < bin.size())
    {
        switch (currentState)
        {
        case State::version:
        {
            const int len = 3;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[i++] - '0') << j;
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
                total += (bin[i++] - '0') << j;

            std::cout << "Type ID: " << total << "\n";

            if (total == 4)
                currentState = State::data;
            else
                currentState = State::lengthId;
        }
        break;

        case State::lengthId:
        {
            int a = bin[i++] - '0';
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
                total += (bin[i++] - '0') << j;
            std::cout << "Total Length: " << total << "\n";
            if (subPackets)
            {
                if (--subPackets)
                    answer += Part1(bin.substr(i, total), highNum);
                else
                    return answer + Part1(bin.substr(i, total), highNum);
            }
            else
                return answer + Part1(bin.substr(i, total), highNum);
            i += total;
            currentState = State::version;
        }
        break;

        case State::numOfSubPackets:
        {
            const int len = 11;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[i++] - '0') << j;
            std::cout << "Num of sub-packets: " << total << "\n";

            if (subPackets)
            {
                if (--subPackets)
                {
                    answer += Part1(bin.substr(i), total);
                    i += bin.substr(i).length();
                }
                else
                    return answer + Part1(bin.substr(i), total);
            }
            else
                return answer + Part1(bin.substr(i), total);
            currentState = State::version;
        }
        break;

        case State::data:
        {
            bool run = true;
            const int len = 5;
            while (run)
            {
                int total = 0;

                for (int j = len - 1; j >= 0; j--)
                    total += (bin[i++] - '0') << j;
                run = total & 0x10;
                std::cout << "Data: " << total << "\n";
            }
            if (subPackets)
                if (--subPackets == 0)
                    return answer;

            currentState = State::version;
        }
        break;

            // default:
            //     i++;
            //     break;
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
    const std::string hex = "C0015000016115A2E0802F182340";
    // ReadTextFile(fileName);
    auto bin = GetBinData(hex);
    std::cout << hex << "\n";
    // std::cout << bin << "\n";

    // Part1(bin);
    std::cout << "Part 1:\n\n" << Part1(bin, 0) << "\n";
}
