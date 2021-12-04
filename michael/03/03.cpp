#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

#include "Utilities/Utilities.h"

int Part1(const std::vector<std::string> &lines);
int Part2(const std::vector<std::string> &lines);
std::vector<std::string> ExtractLines(const std::string &text);
int CalculateRate(const std::vector<std::string> &lines, const std::string& option);

int Part1(const std::vector<std::string> &lines)
{
    return CalculateRate(lines, "gamma") * CalculateRate(lines, "epsilon");
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

int CalculateRate(const std::vector<std::string> &lines, const std::string& option)
{
    const int width = lines[0].length();
    std::vector<unsigned int> gammaRate(width, 0);

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

    int decimalGammaRate = 0;
    int j = 0;
    for (auto i = gammaRate.rbegin(); i != gammaRate.rend(); ++i)
    {
        decimalGammaRate += (*i << j);
        j++;
    }

    if (option == "gamma")
        return decimalGammaRate;
    else if (option == "epsilon")
        return (~decimalGammaRate) & ((1 << gammaRate.size()) - 1);
    std::cerr << "Option '" << option << "' is not allowed\n";
    return 0;
}

int main()
{
    std::string text = ReadTextFile("03/data/input.txt");
    auto lines = ExtractLines(text);

    std::cout << "Part 1: " << Part1(lines) << "\n";
    std::cout << "Part 2: " << Part2(lines) << "\n";

    return 0;
}
