#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <tuple>
#include <vector>

#include "Utilities/Utilities.h"

/*
================================================================================
                                Classes etc.
================================================================================
*/
enum class Rate
{
    Epsilon,
    Gamma
};
enum class Rating
{
    OxygenGenerator,
    Co2Scrubber
};

/*
================================================================================
                            Function Declarations
================================================================================
*/
int Part1(const std::vector<std::string>& lines);
int Part2(const std::vector<std::string>& lines);
std::vector<std::string> ExtractLines(const std::string& text);
int BinaryToDecimal(const std::vector<unsigned int>& binaryVector);
int CalculateRate(const std::vector<std::string>& lines, Rate option);
int CalculateRating(const std::vector<std::string>& lines, Rating option);
std::vector<unsigned int> CountBits(const std::vector<std::string>& lines);

/*
================================================================================
                            Function Definitions
================================================================================
*/
int Part1(const std::vector<std::string>& lines)
{
    return CalculateRate(lines, Rate::Gamma)
           * CalculateRate(lines, Rate::Epsilon);
}

int Part2(const std::vector<std::string>& lines)
{
    return CalculateRating(lines, Rating::OxygenGenerator)
           * CalculateRating(lines, Rating::Co2Scrubber);
}

std::vector<std::string> ExtractLines(const std::string& text)
{
    std::stringstream textStream(text);
    std::vector<std::string> lines;
    std::string tempString;

    while (textStream >> tempString)
        lines.push_back(tempString);

    return lines;
}

int BinaryToDecimal(const std::vector<unsigned int>& binaryVector)
{
    int decimalValue = 0;
    int j = 0;
    for (auto i = binaryVector.rbegin(); i != binaryVector.rend(); i++)
    {
        decimalValue += (*i << j);
        j++;
    }
    return decimalValue;
}

int BinaryToDecimal(const std::string& binaryString)
{
    int decimalValue = 0;
    int j = 0;
    for (auto i = binaryString.rbegin(); i != binaryString.rend(); i++)
    {
        decimalValue += ((*i != '0') << j);
        j++;
    }
    return decimalValue;
}

int CalculateRate(const std::vector<std::string>& lines, Rate option)
{
    const int width = lines[0].length();
    auto gammaRate = CountBits(lines);

    for (int i = 0; i < width; i++)
    {
        if (gammaRate[i] > (lines.size() / 2))
            gammaRate[i] = 1;
        else
            gammaRate[i] = 0;
    }

    int decimalGammaRate = BinaryToDecimal(gammaRate);

    switch (option)
    {
    case Rate::Gamma:
        return decimalGammaRate;

    case Rate::Epsilon:
        return (~decimalGammaRate) & ((1 << gammaRate.size()) - 1);

    default:
        std::cerr << "Option '" << static_cast<int>(option)
                  << "' is not allowed\n";
        return 0;
    }
}

int CalculateRating(const std::vector<std::string>& lines, Rating option)
{
    unsigned int i = 0;
    std::list<std::string> linesList(lines.begin(), lines.end());

    while ((linesList.size() > 1) && (i < lines[0].length()))
    {
        std::vector<std::string> linesReduced(linesList.begin(),
                                              linesList.end());
        auto bitCount = CountBits(linesReduced);
        char charSelected = '0';

        if (bitCount[i] >= ((linesReduced.size() / 2) + (linesReduced.size() % 2)))
            charSelected = '1';

        switch (option)
        {
        case Rating::OxygenGenerator:
            linesList.remove_if([=](auto s) { return s[i] != charSelected; });
            break;

        case Rating::Co2Scrubber:
            linesList.remove_if([=](auto s) { return s[i] == charSelected; });
            break;

        default:
            std::cerr << "Option '" << static_cast<int>(option)
                      << "' is not allowed\n";
            return 0;
        }
        i++;
    }

    std::string binaryNum;
    for (auto line : linesList)
        binaryNum = line;

    return BinaryToDecimal(binaryNum);
}

std::vector<unsigned int> CountBits(const std::vector<std::string>& lines)
{
    int width = lines[0].length();
    std::vector<unsigned int> bitCount(width, 0);
    for (auto line : lines)
        for (int i = 0; i < width; i++)
            if (line[i] == '1')
                bitCount[i]++;

    return bitCount;
}

int main()
{
    std::string text = ReadTextFile("03/data/input.txt");
    auto lines = ExtractLines(text);

    std::cout << "Part 1: " << Part1(lines) << "\n";
    std::cout << "Part 2: " << Part2(lines) << "\n";

    return 0;
}
