/**
 * @file 21.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 21
 * @version 1.0.0
 * @date 2021-12-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <iostream>
#include <string>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Classes
================================================================================
*/
enum class PlayerTurn
{
    player1,
    player2
};

/// Dice class
class Dice
{
    int m_value;
    int m_rolls;

public:
    Dice() : m_value(0), m_rolls(0) {}

    /**
     * @brief Throw dice and get the value
     *
     * @return The value of the dice roll
     */
    int Throw()
    {
        m_rolls++;
        m_value++;

        if (m_value > 100)
            m_value = 1;

        return m_value;
    }

    int GetRolls() const { return m_rolls; }
};

/// Player class
class Player
{
    int m_score;
    int m_position;

public:
    Player(int position) : m_score(0), m_position(position) {}

    void PlayMove(int diceSum)
    {
        m_score += diceSum;
        m_position += diceSum % 10;
    }

    /**
     * @brief Test if player has won
     *
     * @return True if player has won
     */
    bool HasWon() const { return m_score >= 1000; }

    int GetScore() const { return m_score; }
};

/// Game class
class Game
{
    Dice m_dice;
    Player m_player1;
    Player m_player2;
    PlayerTurn m_playerTurn;

public:
    Game(int player1Position, int player2Position)
        : m_dice(), m_player1(player1Position), m_player2(player2Position),
          m_playerTurn(PlayerTurn::player1)
    {
    }

    std::pair<int, int> GetScores() const
    {
        return {m_player1.GetScore(), m_player2.GetScore()};
    }

    int GetNumberOfDiceRolls() const { return m_dice.GetRolls(); }

    bool PlayPlayersRound() { m_dice.Throw(); }
};

/*
================================================================================
                            Function Definitions
================================================================================
*/
static int Part1(int player1Position, int player2Position)
{
    Game game(player1Position, player2Position);
    auto scores = game.GetScores();
    return std::min(scores.first, scores.second) * game.GetNumberOfDiceRolls();
}

static std::pair<int, int> GetStartingPositions(const std::string& text)
{
    auto lines = Split(text, "\n");
    int pos1 = std::stoi(lines[0].substr(28));
    int pos2 = std::stoi(lines[1].substr(28));

    return {pos1, pos2};
}

/**
 * @brief Day 21 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day21(const char* fileName)
{
    const std::string text = ReadTextFile(fileName);
    auto [player1Position, player2Position] = GetStartingPositions(text);
    std::cout << "Part 1: " << Part1(player1Position, player2Position) << "\n";
}
