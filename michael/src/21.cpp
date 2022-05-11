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
#include <utility>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Abstract Classes
================================================================================
*/
/// Base dice class
class BaseDice
{
public:
    /**
     * @brief Get the amount of times rolls
     *
     * @return number of dice rolls
     */
    virtual int64_t GetRolls() const = 0;

    /**
     * @brief Throw dice and get the value
     *
     * @return The value of the dice roll
     */
    virtual int64_t Throw() = 0;
};

/// Base game class
class BaseGame
{
public:
    /**
     * @brief Get the score required to win
     *
     * @return int64_t value of winning score
     */
    virtual int64_t GetScoreToWin() const = 0;

    /**
     * @brief Play the full game
     */
    virtual void Play() = 0;
};

/*
================================================================================
                                Concrete Classes
================================================================================
*/
/// The game type selection
enum class GameType
{
    practice,
    real
};

/// Deterministic dice class
class DeterministicDice : public BaseDice
{
private:
    int64_t m_value; ///< Value on dice
    int64_t m_rolls; ///< Count of number of rolls

public:
    DeterministicDice() : m_value(0), m_rolls(0) {}

    virtual int64_t GetRolls() const override { return m_rolls; }

    virtual int64_t Throw() override
    {
        m_rolls++;
        m_value++;

        if (m_value > 100)
            m_value = 1;

        return m_value;
    }
};

/// Dirac dice
class DiracDice : public BaseDice
{
private:
    int64_t m_value; ///< Value on dice
    int64_t m_rolls; ///< Count of number of rolls

public:
    DiracDice() : m_value(0), m_rolls(0) {}

    virtual int64_t Throw() override { return 0; }
    virtual int64_t GetRolls() const override { return 0; }
};

/// Player class
class Player
{
private:
    int64_t m_score;    ///< Player score
    int64_t m_position; ///< Position tile number minus 1
    BaseGame* m_game;   ///< The game the player is part of

public:
    /**
     * @brief Create a Player object
     *
     * @param position the player starts on
     * @param game the player is part of
     */
    Player(int64_t position, BaseGame* game)
        : m_score(0), m_position(position - 1), m_game(game)
    {
    }

    /**
     * @brief Play a turn
     *
     * @param diceTotal dice that was rolled in the player's turn
     */
    void PlayMove(int64_t diceTotal)
    {
        m_position += diceTotal % 10;
        m_position %= 10;
        m_score += m_position + 1;
    }

    /**
     * @brief Test if player has won
     *
     * @param gameType for selecting the win condition for game type
     * @return true player has won
     * @return false player has not won
     */
    bool HasWon(GameType gameType) const
    {
        return m_score >= m_game->GetScoreToWin();
    }

    /**
     * @brief Get the player's current score
     *
     * @return current score
     */
    int64_t GetScore() const { return m_score; }
};

/// Practice game class
class PracticeGame : public BaseGame
{
private:
    std::array<Player, 2> m_player; ///< Player array
    DeterministicDice m_dice;       ///< Dice for the game
    size_t m_playerId;              ///< Current player's turn ID

    /**
     * @brief Play the player's turn who's go it is
     *
     * @return true The player has won
     * @return false The player has not won
     */
    bool PlayPlayersRound()
    {
        bool playerWon = false;
        int64_t diceSum = m_dice.Throw() + m_dice.Throw() + m_dice.Throw();

        m_player[m_playerId].PlayMove(diceSum);
        playerWon = m_player[m_playerId].HasWon(GameType::practice);

        m_playerId = m_playerId ^ 1; // Toggle
        return playerWon;
    }

public:
    /**
     * @brief Construct a new practice game object
     *
     * @param startingPositions player starting positions
     */
    PracticeGame(std::pair<int64_t, int64_t> startingPositions)
        : m_player{Player(startingPositions.first, this),
                   Player(startingPositions.second, this)},
          m_dice(), m_playerId(0)
    {
    }

    /**
     * @brief Get the score for the loser
     *
     * @return int64_t Score of loser
     */
    int64_t GetLosersScore() const
    {
        return std::min(m_player[0].GetScore(), m_player[1].GetScore());
    }

    virtual int64_t GetScoreToWin() const override { return 1000; }

    /**
     * @brief Get the Number Of times the dice has rolled
     *
     * @return int64_t Number of dice rolls
     */
    int64_t GetNumberOfDiceRolls() const { return m_dice.GetRolls(); }

    virtual void Play() override
    {
        while (!PlayPlayersRound())
        {
        }
    }
};

/// Real game
class RealGame : public BaseGame
{
private:
    std::array<Player, 2> m_players; ///< The players
    DiracDice m_dice;

public:
    /**
     * @brief Construct a new Real Game object
     *
     * @param startingPositions player starting positions
     */
    RealGame(std::pair<int64_t, int64_t> startingPositions)
        : m_players{Player(startingPositions.first, this),
                    Player(startingPositions.second, this)},
          m_dice()
    {
    }

    virtual int64_t GetScoreToWin() const override { return 21; }

    virtual void Play() override {}
};

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Calculate part 1 of the puzzle
 *
 * @param startingPositions for start of game
 * @return Solution to part 1
 */
static int64_t Part1(std::pair<int64_t, int64_t> startingPositions)
{
    PracticeGame game(startingPositions);
    game.Play();
    return game.GetLosersScore() * game.GetNumberOfDiceRolls();
}

/**
 * @brief Calculate part 2 of the puzzle
 *
 * @param startingPositions for start of game
 * @return Solution to part 2
 */
static int64_t Part2(std::pair<int64_t, int64_t> startingPositions)
{
    RealGame game(startingPositions);
    // RealGame game(player1Position, player2Position);
    // game.Play();
    // return game.GetLosersScore() * game.GetNumberOfDiceRolls();
    return 0;
}

/**
 * @brief Get the starting positions out of the text file
 *
 * @param text from file
 * @return pair for player 1 then player 2 starting positions
 */
static std::pair<int64_t, int64_t> GetStartingPositions(const std::string& text)
{
    auto lines = Split(text, "\n");
    int64_t pos1 = std::stoi(lines[0].substr(28));
    int64_t pos2 = std::stoi(lines[1].substr(28));

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
    auto playerPositions = GetStartingPositions(text);

    std::cout << "Part 1: " << Part1(playerPositions) << "\n";
    std::cout << "Part 2: " << Part2(playerPositions) << "\n";
}
