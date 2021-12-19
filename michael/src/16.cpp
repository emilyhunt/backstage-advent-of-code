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
#include <numeric>
#include <string>
#include <vector>

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
    ending,
    end,
};

enum class PacketType
{
    sum = 0,
    product = 1,
    min = 2,
    max = 3,
    data = 4,
    greater = 5,
    less = 6,
    equal = 7,
};

std::ostream& operator<<(std::ostream& os, const PacketType& p)
{
    switch (p)
    {
    case PacketType::sum:
        os << "sum";
        break;

    case PacketType::product:
        os << "product";
        break;

    case PacketType::min:
        os << "min";
        break;

    case PacketType::max:
        os << "max";
        break;

    case PacketType::data:
        os << "data";
        break;

    case PacketType::greater:
        os << "greater";
        break;

    case PacketType::less:
        os << "less";
        break;

    case PacketType::equal:
        os << "equal";
        break;

    
    default:
        os << "unknown: " << static_cast<int>(p);
        break;
    }

    return os;
}

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

void Part1(const std::string& bin, int& index, long int& versionNumSum,
           long long int& packetVal)
{
    // std::cout << bin.substr(index) << "\n";
    State currentState = State::version;
    long long int data = 0;
    std::vector<long long int> packetVals = {};
    PacketType packetType = PacketType::data;

    while (currentState != State::end)
    {
        switch (currentState)
        {
        case State::version:
        {
            const int len = 3;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;
            // std::cout << "Version: " << total << "\n";
            currentState = State::typeId;
            versionNumSum += total;
        }
        break;

        case State::typeId:
        {
            const int len = 3;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;


            packetType = static_cast<PacketType>(total);

            switch (packetType)
            {
            case PacketType::data:
                currentState = State::data;
                break;

            case PacketType::sum:
            case PacketType::product:
            case PacketType::min:
            case PacketType::max:
            case PacketType::greater:
            case PacketType::less:
            case PacketType::equal:
                currentState = State::lengthId;
                break;

            default:
                throw std::invalid_argument("Packet type id not valid");
                break;
            }
            // std::cout << "Packet type ID: " << packetType << "\n";
        }
        break;

        case State::lengthId:
        {
            if (bin[index++] - '0')
                currentState = State::numOfSubPackets;
            else
                currentState = State::totalLength;
            // std::cout << "Length ID: " << a << "\n";
        }
        break;

        case State::totalLength:
        {
            const int len = 15;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;
            // std::cout << "Total Length: " << total << "\n";
            const int start = index;
            while ((index - start) < total)
            {
                Part1(bin, index, versionNumSum, packetVal);
                long long int packetValCopy = packetVal;
                packetVals.push_back(packetValCopy);
            }
            currentState = State::ending;
        }
        break;

        case State::numOfSubPackets:
        {
            const int len = 11;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;
            // std::cout << "Num of sub-packets: " << total << "\n";

            for (int i = 0; i < total; i++)
            {
                Part1(bin, index, versionNumSum, packetVal);
                long long int packetValCopy = packetVal;
                packetVals.push_back(packetValCopy);
            }
            currentState = State::ending;
        }
        break;

        case State::data:
        {
            currentState = (bin[index++] == '1') ? State::data : State::ending;
            const int len = 4;

            for (int i = 0; i < len; i++)
            {
                data <<= 1;
                data += bin[index++] - '0';
            }

            // if (currentState == State::ending)
            //     std::cout << "Data: " << data << "\n";
        }
        break;

        default:
        case State::ending:
            switch (packetType)
            {
            case PacketType::sum:
                packetVal
                    = std::accumulate(packetVals.begin(), packetVals.end(), 0ll);
                break;

            case PacketType::product:
                packetVal = 1;
                for (const auto& subPacketVal : packetVals)
                    packetVal *= subPacketVal;
                break;

            case PacketType::min:
                packetVal
                    = *std::min_element(packetVals.begin(), packetVals.end());
                break;

            case PacketType::max:
                packetVal
                    = *std::max_element(packetVals.begin(), packetVals.end());
                break;

            case PacketType::data:
                packetVal = data;
                data = 0;
                break;

            case PacketType::greater:
                packetVal = packetVals[0] > packetVals[1];
                break;

            case PacketType::less:
                packetVal = packetVals[0] < packetVals[1];
                break;

            case PacketType::equal:
                packetVal = packetVals[0] == packetVals[1];
                break;

            default:
                break;
            }
            currentState = State::end;
            // std::cout << "<=====\n";
            return;
        }
    }

    return;
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
    // std::cout << hex << "\n";

    int index = 0;
    long int part1 = 0;
    long long int part2 = 0;

    Part1(bin, index, part1, part2);
    std::cout << "Part 1: " << part1 << "\n";
    std::cout << "Part 2: " << part2 << "\n";
}
