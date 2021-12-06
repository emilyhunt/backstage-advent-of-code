/**
 * @file 04.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 4
 * @version 1.0.0
 * @date 2021-12-04
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <array>
#include <cstdlib>
#include <exception>
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
/**
 * @brief BingoCard to play bingo with
 */
class BingoCard
{
private:
    std::array<std::array<int, 5>, 5> m_grid;
    std::array<std::array<bool, 5>, 5> m_blotted;

public:
    static int cardCount;
    BingoCard(const std::string& cardText) : m_grid{0}, m_blotted{false}
    {
        std::stringstream cardTextStream(cardText);
        for (auto& row : m_grid)
            for (auto& num : row)
                cardTextStream >> num;
    }

    void Blot(int ball)
    {
        for (size_t i = 0; i < m_grid.size(); i++)
        {
            for (size_t j = 0; j < m_grid[0].size(); j++)
            {
                if (m_grid[i][j] == ball)
                {
                    m_blotted[i][j] = true;
                }
            }
        }
    }

    int GetScore() const
    {
        int sum = 0;
        for (size_t row = 0; row < m_grid.size(); row++)
            for (size_t col = 0; col < m_grid[row].size(); col++)
                if (!m_blotted[row][col])
                    sum += m_grid[row][col];
        return sum;
    }

    bool CheckForLine() const
    {
        // Check rows
        for (const auto& row : m_blotted)
            if (std::all_of(row.begin(), row.end(), [](bool i) { return i; }))
                return true;

        // Check cols
        for (size_t col = 0; col < m_blotted[0].size(); col++)
        {
            size_t sum = 0;
            for (const auto& row : m_blotted)
                if (row[col])
                    sum++;

            if (sum == m_blotted[col].size())
                return true;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const BingoCard& card);
};

/**
 * @brief BingoGame to play bingo!
 */
class BingoGame
{
private:
    std::list<BingoCard> m_cards;
    std::vector<int> m_balls;
    std::vector<int>::iterator m_ballsIter;

public:
    BingoGame(const std::string& textFile)
        : m_cards{}, m_balls{}, m_ballsIter(m_balls.begin())
    {
        const std::regex doubleNewline("(.*)\\n\\n");
        std::smatch match;
        std::regex_search(textFile, match, doubleNewline);

        std::string ballsString = match[1].str();

        const std::regex firstVal("(\\d+),");
        const std::regex vals(",(\\d+)");
        std::regex_search(ballsString, match, firstVal);
        m_balls.push_back(std::stoi(match[1]));

        auto ballBegin = std::sregex_iterator(ballsString.begin(),
                                              ballsString.end(), vals);
        auto end = std::sregex_iterator();
        for (auto i = ballBegin; i != end; i++)
        {
            match = *i;
            m_balls.push_back(std::stoi(match[1]));
        }

        const std::regex bingoCardRe("(?: *\\d+ +\\d+ +\\d+ +\\d+ +\\d+\\n){4}"
                                     " *\\d+ +\\d+ +\\d+ +\\d+ +\\d+");
        auto cardBegin = std::sregex_iterator(textFile.begin(), textFile.end(),
                                              bingoCardRe);
        for (auto i = cardBegin; i != end; i++)
        {
            BingoCard bingoCard((*i)[0]);
            m_cards.push_back(bingoCard);
        }

        m_ballsIter = m_balls.begin();
    }

    int GetCurrentBall() const { return *m_ballsIter; }

    /**
     * @brief Get the score if someone won a line, or 0 if noone won
     *
     * @return int a score of the first winner found or 0
     */
    int GetLineWinnerScore() const
    {
        for (const auto& card : m_cards)
            if (card.CheckForLine())
                return card.GetScore();
        return 0;
    }

    int GetCardsRemaining() const { return m_cards.size(); }

    void DrawNextBall()
    {
        m_ballsIter++;
        if (m_ballsIter == m_balls.end())
            throw std::out_of_range("Nobody won!");
    }

    void BlotCards()
    {
        for (auto& card : m_cards)
            card.Blot(*m_ballsIter);
    }

    void RemoveWinners()
    {
        m_cards.remove_if([](BingoCard card) { return card.CheckForLine(); });
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const BingoGame& bingoGame);
};

/**
 * @brief BingoCard object representation to std::ostream
 *
 * @param os Output stream
 * @param card BingoCard to output
 * @return std::ostream& reference to modified output stream
 */
std::ostream& operator<<(std::ostream& os, const BingoCard& card)
{
    os << "\n";
    for (const auto& row : card.m_grid)
    {
        for (const auto& num : row)
            os << num << "\t";
        os << "\n";
    }
    os << "\n";
    return os;
}

/**
 * @brief BingoGame object representation to std::ostream
 *
 * @param os Output stream
 * @param card BingoGame to output
 * @return std::ostream& reference to modified output stream
 */
std::ostream& operator<<(std::ostream& os, const BingoGame& bingoGame)
{
    bool doneFirstRun = false;
    for (const auto& item : bingoGame.m_balls)
    {
        if (!doneFirstRun)
            doneFirstRun = true;
        else
            os << " ";
        os << item;
    }
    os << "\n\n";
    for (const auto& card : bingoGame.m_cards)
        os << card;
    return os;
}

/*
================================================================================
                            Function Declarations
================================================================================
*/
int Part1(BingoGame& game);
int Part2(BingoGame& game);

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Solve part 1
 *
 * @param game bingo game to play
 * @return int Solution
 */
int Part1(BingoGame& game)
{
    game.BlotCards();

    while (!game.GetLineWinnerScore())
    {
        game.DrawNextBall();
        game.BlotCards();
    }

    return game.GetLineWinnerScore() * game.GetCurrentBall();
}

/**
 * @brief Solve part 2
 *
 * @param game bingo game to play
 * @return int Solution
 */
int Part2(BingoGame& game)
{
    game.RemoveWinners();

    while (game.GetCardsRemaining() > 1)
    {
        game.DrawNextBall();
        game.BlotCards();
        game.RemoveWinners();
    }

    return Part1(game);
}

/**
 * @brief Start of program execution
 *
 * @return int return 0 for normal running
 */
int main()
{
    std::string text = ReadTextFile("04/data/input.txt");
    BingoGame bingoGame(text);

    std::cout << "Part 1: " << Part1(bingoGame) << "\n";
    std::cout << "Part 2: " << Part2(bingoGame) << "\n";

    return 0;
}
