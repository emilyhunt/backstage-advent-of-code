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
#include <map>
#include <string>
#include <tuple>
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
     * @return true player has won
     * @return false player has not won
     */
    bool HasWon() const { return m_score >= m_game->GetScoreToWin(); }

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
        playerWon = m_player[m_playerId].HasWon();

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
        : m_player{Player(startingPositions.first, nullptr),
                   Player(startingPositions.second, nullptr)},
          m_dice(),
          m_playerId(0)
    {
        m_player = {Player(startingPositions.first, this),
                    Player(startingPositions.second, this)};
    }

    virtual ~PracticeGame() {}

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
    /// Score key with player 1 position, then player 2, then player 1 and 2
    /// scores
    using ScoreKey = std::tuple<int64_t, int64_t, int64_t, int64_t>;
    int64_t m_player1Position; ///< Position of player 1
    int64_t m_player2Position; ///< Position of player 2

    /// Final amounts of wins of both players from given starting points and
    /// scores
    std::map<ScoreKey, std::pair<int64_t, int64_t>> m_scores;

    /// Answer to puzzle once solved
    std::pair<int64_t, int64_t> m_answer;
    bool m_foundAnswer; ///< Indicates puzzle has been solved

public:
    /**
     * @brief Construct a new Real Game object
     *
     * @param startingPositions player starting positions
     */
    RealGame(std::pair<int64_t, int64_t> startingPositions)
        : m_player1Position(startingPositions.first),
          m_player2Position(startingPositions.second),
          m_scores(), m_answer{0, 0}, m_foundAnswer(false)
    {
    }

    virtual ~RealGame() {}

    virtual int64_t GetScoreToWin() const override { return 21; }

    virtual void Play() override
    {
        ScoreKey startingKey
            = {m_player1Position - 1, m_player2Position - 1, 0, 0};
        m_answer = GetWins(startingKey);
        m_foundAnswer = true;
    }

    /**
     * @brief Get the answer puzzle
     *
     * @return Answer of puzzle
     */
    std::pair<int64_t, int64_t> GetAnswer() const
    {
        if (!m_foundAnswer)
            throw std::runtime_error("Answer not found!");
        return m_answer;
    }

private:
    /**
     * @brief Get the amount of wins for both players
     *
     * @param key From starting positions and scores given by key
     * @return Amound of wins for player 1 then 2
     */
    std::pair<int64_t, int64_t> GetWins(const ScoreKey& key)
    {
        const auto& [position1, position2, score1, score2] = key;

        if (score1 >= GetScoreToWin())
            return {1, 0};
        if (score2 >= GetScoreToWin())
            return {0, 1};
        if (m_scores.find(key) != m_scores.end())
            return m_scores[key];

        const std::array<int64_t, 3> diceSides{1, 2, 3};

        std::pair<int64_t, int64_t> answer{0, 0};
        for (const auto& dice1 : diceSides)
        {
            for (const auto& dice2 : diceSides)
            {
                for (const auto& dice3 : diceSides)
                {
                    // Swap round to play next player
                    const int64_t newPosition1
                        = (position1 + dice1 + dice2 + dice3) % 10;
                    const int64_t newScore1 = score1 + newPosition1 + 1;

                    const auto [x, y]
                        = GetWins({position2, newPosition1, score2, newScore1});

                    // Swap back again
                    answer = std::pair<int64_t, int64_t>(answer.first + y,
                                                         answer.second + x);
                }
            }
        }

        m_scores[key] = answer;
        return answer;
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
    game.Play();
    auto answer = game.GetAnswer();
    return std::max(answer.first, answer.second);
}

/**
 * @brief Get the starting positions out of the text file
 *
 * @param text from file
 * @return pair for player 1 then player 2 starting positions
 */
static std::pair<int64_t, int64_t> GetStartingPositions(const std::string& text)
{
    auto lines = SplitLines(text);
    return {std::stoi(lines[0].substr(28)), std::stoi(lines[1].substr(28))};
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
