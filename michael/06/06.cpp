#include <iostream>
#include <vector>

#include "Utilities/Utilities.h"

/*
================================================================================
                            Function Declarations
================================================================================
*/

/*
================================================================================
                            Function Definitions
================================================================================
*/
int Part1(const std::vector<int> numbers) { return 0; }

int main()
{
    std::vector<int> numbers = ReadNumbersFile("06/data/test.txt");

    PrintNumbers(numbers);

    // std::cout << "Part 1: " << Part1(numbers) << "\n";

    return 0;
}
