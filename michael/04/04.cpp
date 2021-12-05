#include <cstdlib>
#include <iostream>
#include <list>
#include <regex>
#include <vector>

#include "Utilities/Utilities.h"

/*
================================================================================
                                Classes etc
================================================================================
*/
class BingoCard
{
};

class BingoGame
{
private:
    std::list<BingoCard> bingoCards;
    std::vector<int> ballOrder;

public:
    BingoGame(const std::string& textFile)
    {
        const std::regex doubleNewline("(.*)\\n\\n");
        std::smatch balls;
        std::regex_search(textFile, balls, doubleNewline);

        std::string ballsString = balls[1].str();

        const std::regex firstVal("(\\d+),");
        const std::regex vals(",(\\d+)");
        std::smatch num;
        std::regex_search(ballsString, num, firstVal);
        ballOrder.push_back(std::stoi(num[1]));

        auto begin = std::sregex_iterator(ballsString.begin(),
                                          ballsString.end(), vals);
        for (auto i = begin; i != std::sregex_iterator(); i++)
        {
            num = *i;
            ballOrder.push_back(std::stoi(num[1]));
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const BingoGame& bingoGame);
};

std::ostream& operator<<(std::ostream& os, const BingoGame& bingoGame)
{
    os << "Balls: ";
    bool doneFirstRun = false;
    for (const auto& item : bingoGame.ballOrder)
    {
        if (!doneFirstRun)
            doneFirstRun = true;
        else
            os << ", ";
        os << item;
    }
    os << "\n";
    return os;
}

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
int Part1() { return 0; }

int main()
{
    std::string text = ReadTextFile("04/data/test.txt");
    BingoGame bingoGame(text);

    std::cout << bingoGame;

    // std::cout << "Part 1: " << Part1() << "\n";

    return 0;
}
