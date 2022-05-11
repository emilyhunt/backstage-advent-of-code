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

static const int WINNING_SCORE = 1000; ///< Winning score

/*
================================================================================
                                    Classes
================================================================================
*/
/**
 * @brief The current player turn
 */
enum class PlayerTurn
{
    player1, ///< Player 1
    player2  ///< Player 2
};

/// Dice class
class Dice
{
private:
    int m_value; ///< Value on dice
    int m_rolls; ///< Count of number of rolls

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

    /**
     * @brief Get the amount of times rolls
     *
     * @return number of dice rolls
     */
    int GetRolls() const { return m_rolls; }
};

/// Player class
class Player
{
private:
    int m_score;    ///< Player score
    int m_position; ///< Position tile number minus 1

public:
    /**
     * @brief Create a Player object
     *
     * @param position the player starts on
     */
    Player(int position) : m_score(0), m_position(position - 1) {}

    /**
     * @brief Play a turn
     *
     * @param diceTotal dice that was rolled in the player's turn
     */
    void PlayMove(int diceTotal)
    {
        m_position += diceTotal % 10;
        m_position %= 10;
        m_score += m_position + 1;
    }

    /**
     * @brief Test if player has won
     *
     * @return True if player has won
     */
    bool HasWon() const { return m_score >= WINNING_SCORE; }

    /**
     * @brief Get the player's current score
     *
     * @return current score
     */
    int GetScore() const { return m_score; }
};

/// Game class
class Game
{
private:
    Dice m_dice;                    ///< Dice for the game
    std::array<Player, 2> m_player; ///< Player array
    PlayerTurn m_playerTurn;        ///< Current player's turn

    /**
     * @brief Play the player's turn who's go it is
     *
     * @return true The player has won
     * @return false The player has not won
     */
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
    /**
     * @brief Construct a new Game object
     *
     * @param player1Position starting position of player 1
     * @param player2Position starting position of player 2
     */
    Game(int player1Position, int player2Position)
        : m_dice(), m_player{{player1Position, player2Position}},
          m_playerTurn(PlayerTurn::player1)
    {
    }

    /**
     * @brief Get the score for the loser
     *
     * @return int Score of loser
     */
    int GetLosersScore() const
    {
        return std::min(m_player[0].GetScore(), m_player[1].GetScore());
    }

    /**
     * @brief Get the Number Of times the dice has rolled
     *
     * @return int Number of dice rolls
     */
    int GetNumberOfDiceRolls() const { return m_dice.GetRolls(); }

    /**
     * @brief Play the full game
     */
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
/**
 * @brief Calculate part 1 of the puzzle
 *
 * @param player1Position for start of game
 * @param player2Position for start of game
 * @return Solution to part 1
 */
static int Part1(int player1Position, int player2Position)
{
    Game game(player1Position, player2Position);
    game.Play();
    return game.GetLosersScore() * game.GetNumberOfDiceRolls();
}

/**
 * @brief Get the starting positions out of the text file
 *
 * @param text from file
 * @return pair for player 1 then player 2 starting positions
 */
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
