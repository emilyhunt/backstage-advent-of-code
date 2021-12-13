/**
 * @file 05.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 5
 * @version 1.0.0
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Classes etc
================================================================================
*/
/**
 * @brief Any point on a line
 */
class Point
{
private:
    int m_x; ///< X coordinate
    int m_y; ///< Y coordinate

public:
    /**
     * @brief Construct a new Point object
     *
     * @param x Coordinate on the x axis
     * @param y Coordinate on the y axis
     */
    Point(int x, int y) : m_x(x), m_y(y) {}

    /**
     * @brief String representation of point
     *
     * @return std::string representation of point in format "x,y"
     */
    std::string str() const
    {
        std::stringstream ss;
        ss << m_x << "," << m_y;
        return ss.str();
    }

    /**
     * @brief Equality operator for comparing Point objects
     *
     * @param other Point to compare to
     * @return true Point coordinates match
     * @return false Point coordinates don't match
     */
    bool operator==(const Point& other) const
    {
        return (this->m_x == other.m_x) && (this->m_y == other.m_y);
    }

    /**
     * @brief Get the x coordinate
     *
     * @return int X coordinate
     */
    int GetX() const { return m_x; }

    /**
     * @brief Get the y coordinate
     *
     * @return int Y coordinate
     */
    int GetY() const { return m_y; }

    /**
     * @brief Get the Coordinate as a pair
     *
     * @return std::pair<int, int> x then y pair
     */
    std::pair<int, int> GetCoord() const { return std::make_pair(m_x, m_y); }

    /**
     * @brief Distance between two points
     *
     * @param other to measure the distance to
     * @return int Chebyshev distance from this point to other point
     */
    int DistanceTo(const Point& other) const
    {
        return std::max(std::abs(this->m_x - other.m_x),
                        std::abs(this->m_y - other.m_y));
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point);
};

namespace std
{
/**
 * @brief Hash function for Point
 */
template <>
struct hash<Point>
{
    /**
     * @brief Call operator for hash object, for use with std::unordered_map
     *
     * @param point point object to hash
     * @return std::size_t hash of object
     */
    std::size_t operator()(const Point& point) const
    {
        return std::hash<std::string>{}(point.str());
    }
};
}

/**
 * @brief A line of points
 */
class Line
{
private:
    Point m_start; ///< First point on line
    Point m_end;   ///< Final point on line

public:
    /**
     * @brief Construct a new Line object
     *
     * @param start the first point of the line of points
     * @param end the last point of the line of points
     */
    Line(const Point& start, const Point& end) : m_start(start), m_end(end) {}

    /**
     * @brief Finds if a point is horizontal or vertical, i.e not diagonal
     *
     * @return true if horizontal or vertical
     * @return false if diagonal
     */
    bool IsHorizontalOrVertical() const
    {
        return (m_start.GetX() == m_end.GetX())
               || (m_start.GetY() == m_end.GetY());
    }

    /**
     * @brief Finds if a point is diagonal, i.e not horizontal or vertical
     *
     * @return true if diagonal
     * @return false if horizontal or vertical
     */
    bool IsDiagonal() const { return !IsHorizontalOrVertical(); }

    /**
     * @brief Get the all Points on the line
     *
     * @return std::vector<Point> the points as a vector of Point objects
     */
    std::vector<Point> GetAllPoints() const
    {
        std::vector<Point> points;
        points.push_back(m_start);
        auto [x1, y1] = m_start.GetCoord();
        auto [x2, y2] = m_end.GetCoord();

        int xDir = Sign<int>(x2 - x1);
        int yDir = Sign<int>(y2 - y1);

        while (!((x1 == x2) && (y1 == y2)))
        {
            x1 += xDir;
            y1 += yDir;
            points.push_back(Point(x1, y1));
        }

        return points;
    }

    friend std::ostream& operator<<(std::ostream& os, const Line& line);
};

/**
 * @brief A collection of horizontal, vertical and diagonal lines
 */
class Lines
{
private:
    std::vector<Line> m_lines;             ///< All lines on grid
    std::unordered_map<Point, int> m_grid; ///< Grid of lines

    /**
     * @brief Paint the line onto the grid
     *
     * @param line to paint
     */
    void PaintLine(const Line& line)
    {
        auto points = line.GetAllPoints();
        for (const auto& point : points)
            PaintPoint(point);
    }

    /**
     * @brief Paint a point onto grid
     *
     * @param point location to paint
     */
    void PaintPoint(const Point& point)
    {
        if (m_grid.count(point))
            m_grid[point]++;
        else
            m_grid.insert(std::make_pair(point, 1));
    }

public:
    /**
     * @brief Construct a new Lines object
     *
     * @param text file to build lines from
     */
    Lines(const std::string& text) : m_lines(), m_grid()
    {
        std::regex lineRegex("(\\d+),(\\d+) -> (\\d+),(\\d+)");
        std::smatch match;
        auto begin = std::sregex_iterator(text.begin(), text.end(), lineRegex);
        auto end = std::sregex_iterator();
        std::array<int, 4> num;

        for (auto i = begin; i != end; i++)
        {
            match = *i;
            for (std::size_t i = 0; i < num.size(); i++)
                num[i] = std::stoi(match[i + 1].str());
            m_lines.push_back(
                Line(Point(num[0], num[1]), Point(num[2], num[3])));
        }
    }

    /**
     * @brief Print painted grid locations
     */
    void PrintGrid() const
    {
        for (const auto& item : m_grid)
            std::cout << item.first << ": " << item.second << "\n";
    }

    /**
     * @brief Count how many intersections of lines there currently are
     *
     * @return int amount of intersections
     */
    int CountIntersections() const
    {
        return std::count_if(m_grid.begin(), m_grid.end(),
                             [](std::pair<Point, int> i)
                             { return i.second > 1; });
    }

    /**
     * @brief Paint only horizontal and vertical lines
     */
    void PaintHorizontalAndVerticalLines()
    {
        for (const auto& line : m_lines)
        {
            if (line.IsHorizontalOrVertical())
            {
                PaintLine(line);
            }
        }
    }

    /**
     * @brief Paint only diagonal lines
     */
    void PaintDiagonalLines()
    {
        for (const auto& line : m_lines)
        {
            if (line.IsDiagonal())
            {
                PaintLine(line);
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Lines& lines);
};

/**
 * @brief Point object representation to std::ostream
 *
 * @param os Output stream
 * @param point Point to output
 * @return std::ostream& reference to modified output stream
 */
std::ostream& operator<<(std::ostream& os, const Point& point)
{
    os << point.m_x << "," << point.m_y;
    return os;
}

/**
 * @brief Line object representation to std::ostream
 *
 * @param os Output stream
 * @param line Line to output
 * @return std::ostream& reference to modified output stream
 */
std::ostream& operator<<(std::ostream& os, const Line& line)
{
    os << line.m_start << " -> " << line.m_end << " : "
       << line.m_start.DistanceTo(line.m_end);
    return os;
}

/**
 * @brief Lines object representation to std::ostream
 *
 * @param os Output stream
 * @param lines Lines to output
 * @return std::ostream& reference to modified output stream
 */
std::ostream& operator<<(std::ostream& os, const Lines& lines)
{
    for (const auto& line : lines.m_lines)
        os << line << "\n";
    return os;
}

/*
================================================================================
                            Function Declarations
================================================================================
*/
static int Part1(Lines& lines);
static int Part2(Lines& lines);

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Solve part 1
 *
 * @param lines lines object to use
 * @return int Solution
 */
static int Part1(Lines& lines)
{
    lines.PaintHorizontalAndVerticalLines();
    return lines.CountIntersections();
}

/**
 * @brief Solve part 2
 *
 * @param lines lines object to use
 * @return int Solution
 */
static int Part2(Lines& lines)
{
    lines.PaintDiagonalLines();
    return lines.CountIntersections();
}

/**
 * @brief Day 5 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day05(const char* fileName)
{
    std::string text = ReadTextFile(fileName);
    Lines lines(text);

    std::cout << "Part 1: " << Part1(lines) << "\n";
    std::cout << "Part 2: " << Part2(lines) << "\n";
}
