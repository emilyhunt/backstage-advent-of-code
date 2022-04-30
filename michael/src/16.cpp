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
/**
 * @brief States of the state machine
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

/**
 * @brief Packet type ID
 */
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

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Print out the PacketType as a string representation
 * 
 * @param os output stream
 * @param p packet type enum
 * @return std::ostream& reference to modified output stream
 */
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

/**
 * @brief Map a hex character to a binary string part
 * 
 * @param ch hex character
 * @return std::string binary string of length 4
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

/**
 * @brief Get the binary string from hex string
 * 
 * @param hex string
 * @return std::string of 1s and 0s
 */
std::string GetBinData(const std::string& hex)
{
    std::string bin;
    for (const auto& ch : hex)
        bin += HexCharToBin(ch);
    return bin;
}

/**
 * @brief Solve part 1 and 2
 * 
 * @param bin binary string
 * @param index current index position in binary string
 * @param versionNumSum sum of version numbers (part 1)
 * @param packetVal packet value (part 2)
 */
void Solve(const std::string& bin, int& index, int64_t& versionNumSum,
           int64_t& packetVal)
{
    State currentState = State::version;
    int64_t data = 0;
    std::vector<int64_t> packetVals = {};
    PacketType packetType = PacketType::data;

    while (currentState != State::end)
    {
        int64_t startingVal = 0;

        switch (currentState)
        {
        case State::version:
        {
            const int64_t len = 3;
            int64_t total = 0;

            for (int64_t j = len - 1; j >= 0; j--)
                total += static_cast<int64_t>(bin[index++] - '0') << j;
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
        }
        break;

        case State::lengthId:
        {
            if (bin[index++] - '0')
                currentState = State::numOfSubPackets;
            else
                currentState = State::totalLength;
        }
        break;

        case State::totalLength:
        {
            const int len = 15;
            int total = 0;

            for (int j = len - 1; j >= 0; j--)
                total += (bin[index++] - '0') << j;
            const int start = index;
            while ((index - start) < total)
            {
                Solve(bin, index, versionNumSum, packetVal);
                int64_t packetValCopy = packetVal;
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

            for (int i = 0; i < total; i++)
            {
                Solve(bin, index, versionNumSum, packetVal);
                int64_t packetValCopy = packetVal;
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
        }
        break;

        default:
        case State::ending:
            switch (packetType)
            {
            case PacketType::sum:
                packetVal = std::accumulate(packetVals.begin(),
                                            packetVals.end(), startingVal);
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

    int index = 0;
    int64_t part1 = 0;
    int64_t part2 = 0;

    Solve(bin, index, part1, part2);
    std::cout << "Part 1: " << part1 << "\n";
    std::cout << "Part 2: " << part2 << "\n";
}
