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

#include "Utilities/Utilities.h"

/*
================================================================================
                                Classes etc
================================================================================
*/
int Sign(int val) { return (0 < val) - (val < 0); }

/**
 * @brief Point class
 */
class Point
{
private:
    int m_x;
    int m_y;

public:
    Point(int x, int y) : m_x(x), m_y(y) {}

    std::string str() const
    {
        std::stringstream ss;
        ss << m_x << "," << m_y;
        return ss.str();
    }

    bool operator==(const Point& other) const
    {
        return (this->m_x == other.m_x) && (this->m_y == other.m_y);
    }

    int GetX() const { return m_x; }
    int GetY() const { return m_y; }
    std::pair<int, int> GetCoord() const { return std::make_pair(m_x, m_y); }

    int DistanceTo(const Point& other) const
    {
        return std::max(std::abs(this->m_x - other.m_x),
                        std::abs(this->m_y - other.m_y));
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point);
};

template <>
struct std::hash<Point>
{
    std::size_t operator()(const Point& point) const
    {
        return std::hash<std::string>{}(point.str());
    }
};

class Line
{
private:
    Point m_start;
    Point m_end;

public:
    Line(const Point& start, const Point& end) : m_start(start), m_end(end) {}

    bool IsHorizontalOrVertical() const
    {
        return (m_start.GetX() == m_end.GetX())
               || (m_start.GetY() == m_end.GetY());
    }

    std::vector<Point> GetAllPoints() const
    {
        std::vector<Point> points;
        points.push_back(m_start);
        auto [x1, y1] = m_start.GetCoord();
        auto [x2, y2] = m_end.GetCoord();

        int xDir = Sign(x2 - x1);
        int yDir = Sign(y2 - y1);

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

class Lines
{
private:
    std::vector<Line> m_lines;
    std::unordered_map<Point, int> m_grid;

    void PaintLine(const Line& line)
    {
        auto points = line.GetAllPoints();
        for (const auto& point : points)
            PaintPoint(point);
    }

    void PaintPoint(const Point& point)
    {
        if (m_grid.count(point))
            m_grid[point]++;
        else
            m_grid.insert(std::make_pair(point, 1));
    }

public:
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

    void PrintGrid() const
    {
        for (const auto& item : m_grid)
            std::cout << item.first << ": " << item.second << "\n";
    }

    int CountIntersections() const
    {
        return std::count_if(m_grid.begin(), m_grid.end(),
                             [](std::pair<Point, int> i)
                             { return i.second > 1; });
    }

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

    friend std::ostream& operator<<(std::ostream& os, const Lines& lines);
};

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    os << point.m_x << "," << point.m_y;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Line& line)
{
    os << line.m_start << " -> " << line.m_end << " : "
       << line.m_start.DistanceTo(line.m_end);
    return os;
}

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
int Part1(const Lines& lines);
int Part2(const Lines& lines);

/*
================================================================================
                            Function Definitions
================================================================================
*/
int Part1(Lines& lines)
{
    lines.PaintHorizontalAndVerticalLines();
    return lines.CountIntersections();
}

int Part2(Lines& lines)
{
    // lines.PaintDiagonalLines();
    return lines.CountIntersections();
}

int main()
{
    std::string text = ReadTextFile("05/data/input.txt");
    Lines lines(text);

    std::cout << "Part 1: " << Part1(lines) << "\n";
    std::cout << "Part 2: " << Part2(lines) << "\n";

    return 0;
}
