/**
 * @file 21.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 21
 * @version 1.0.0
 * @date 2022-05-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <string>

#include "Days.h"
#include "Utilities.h"

static const int WINNING_SCORE = 1000;

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
private:
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
private:
    int m_score;    ///< Player score
    int m_position; ///< Position tile number minus 1

public:
    Player(int position) : m_score(0), m_position(position - 1) {}

    void PlayMove(int diceSum)
    {
        diceSum %= 10;
        m_position += diceSum;
        m_position %= 10;
        m_score += m_position + 1;
    }

    /**
     * @brief Test if player has won
     *
     * @return True if player has won
     */
    bool HasWon() const { return m_score >= WINNING_SCORE; }

    int GetScore() const { return m_score; }
};

/// Game class
class Game
{
private:
    Dice m_dice;
    std::array<Player, 2> m_player;
    PlayerTurn m_playerTurn;

    bool PlayPlayersRound()
    {
        bool playerWon = false;
        int diceSum = m_dice.Throw() + m_dice.Throw() + m_dice.Throw();
        size_t playerIndex = (m_playerTurn == PlayerTurn::player1) ? 0 : 1;

        m_player[playerIndex].PlayMove(diceSum);
        playerWon = m_player[playerIndex].HasWon();

        m_playerTurn = (m_playerTurn == PlayerTurn::player1)
                           ? PlayerTurn::player2
                           : PlayerTurn::player1;
        return playerWon;
    }

public:
    Game(int player1Position, int player2Position)
        : m_dice(), m_player{{player1Position, player2Position}},
          m_playerTurn(PlayerTurn::player1)
    {
    }

    std::pair<int, int> GetScores() const
    {
        return {m_player[0].GetScore(), m_player[1].GetScore()};
    }

    int GetLosersScore() const
    {
        return std::min(m_player[0].GetScore(), m_player[1].GetScore());
    }

    int GetNumberOfDiceRolls() const { return m_dice.GetRolls(); }

    void Play()
    {
        while (!PlayPlayersRound())
        {
        }
    }
};

/*
================================================================================
                            Function Definitions
================================================================================
*/
static int Part1(int player1Position, int player2Position)
{
    Game game(player1Position, player2Position);
    game.Play();
    return game.GetLosersScore() * game.GetNumberOfDiceRolls();
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
