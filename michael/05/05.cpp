#include <iostream>
#include <vector>

#include "Utilities/Utilities.h"

/*
================================================================================
                                Classes etc
================================================================================
*/
class Point
{
private:
    int m_x;
    int m_y;

public:
    Point(int x, int y) : m_x(x), m_y(y) {}
};

class Line
{
private:
    Point m_start;
    Point m_end;

public:
    Line(const Point& start, const Point& end) : m_start(m_start), m_end(end) {}
};

class Lines
{
private:
    std::vector<Line> lines;

public:
    Lines(const std::string& text)
    {
        std::cout << text << "\n";
    }
};

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
    std::string text = ReadTextFile("05/data/input.txt");

    Lines lines(text);

    std::cout << "Part 1: " << Part1() << "\n";

    return 0;
}
