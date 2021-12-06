#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "Days.h"
#include "Utilities.h"

int main(int argc, char** argv)
{
    std::vector<const char*> args;
    for (int i = 0; i < argc; i++)
        args.push_back(argv[i]);

    if (args.size() != 3)
        throw std::invalid_argument("Wrong number of args");

    int dayId = std::atoi(args[1]);
    switch (dayId)
    {
    case 1:
        Day1(args[2]);
        break;

    case 2:
        Day2(args[2]);
        break;

    case 3:
        Day3(args[2]);
        break;

    case 4:
        Day4(args[2]);
        break;

    case 5:
        Day5(args[2]);
        break;

    case 6:
        Day6(args[2]);
        break;

    default:
        throw std::invalid_argument(args[1]);
        break;
    }
}