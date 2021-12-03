#include <array>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "Utilities/Utilities.h"

int Part1(const std::vector<std::string> &lines);
int Part2(const std::vector<std::string> &lines);
std::vector<std::string> ExtractLines(const std::string &text);
int CalculateGammaRate(const std::vector<std::string> &lines);
int CalculateEpsilonRate(const std::vector<std::string> &lines);

int Part1(const std::vector<std::string> &lines)
{
    return CalculateGammaRate(lines) * CalculateEpsilonRate(lines);
}

int Part2(const std::vector<std::string> &lines)
{
    return 0;
}

std::vector<std::string> ExtractLines(const std::string &text)
{
    std::stringstream textStream(text);
    std::vector<std::string> lines;
    std::string tempString;

    while (textStream >> tempString)
        lines.push_back(tempString);

    return lines;
}

void PrintLines(const std::vector<std::string> &lines)
{
    for (auto &line : lines)
    {
        std::cout << line << "\n";
    }
}

int CalculateGammaRate(const std::vector<std::string> &lines)
{
    const int width = lines[0].length();
    std::vector<int> gammaRate(width, 0);

    for (int i = 0; i < width; i++)
    {
        for (auto &line : lines)
        {
            if (line[i] == '1')
                gammaRate[i] += 1;
        }
        if (gammaRate[i] > (lines.size() / 2))
            gammaRate[i] = 1;
        else
            gammaRate[i] = 0;
    }

    // gammaRate
    return gammaRate[0];
}

int CalculateEpsilonRate(const std::vector<std::string> &lines)
{
    return 1;
}

int main()
{
    std::string text = ReadTextFile("03/data/test.txt");
    auto lines = ExtractLines(text);

    std::cout << "Part 1: " << Part1(lines) << "\n";
    // std::cout << "Part 2: " << Part2(instructions) << "\n";

    return 0;
}
