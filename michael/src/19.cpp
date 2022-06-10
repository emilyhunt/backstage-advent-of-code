/**
 * @file 19.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 19
 * @version 1.0.0
 * @date 2021-12-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#define _USE_MATH_DEFINES

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                    Classes
================================================================================
*/

using Vector = std::array<int64_t, 3>;

static double DegToRad(double angle) { return M_PI / 180.0 * angle; }

class Rotation
{
private:
    std::array<std::array<int64_t, 3>, 3> m_matrix;

public:
    Rotation() : m_matrix{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}} {}

    Rotation(double yaw, double pitch, double roll) : m_matrix()
    {
        int64_t c1 = static_cast<int64_t>(std::cos(roll));
        int64_t c2 = static_cast<int64_t>(std::cos(pitch));
        int64_t c3 = static_cast<int64_t>(std::cos(yaw));
        int64_t s1 = static_cast<int64_t>(std::sin(roll));
        int64_t s2 = static_cast<int64_t>(std::sin(pitch));
        int64_t s3 = static_cast<int64_t>(std::sin(yaw));

        m_matrix = {
            {{(c2 * c3), (-s2), (c2 * s3)},
             {(s1 * s3 + c1 * c3 * s2), (c1 * c2), (c1 * s2 * s3 - c3 * s1)},
             {(c3 * s1 * s2 - c1 * s3), (c2 * s1), (c1 * c3 + s1 * s2 * s3)}}};
    }

    /**
     * @brief Construct euler angles from internal rotation matrix
     *
     * https://en.wikipedia.org/wiki/Euler_angles
     * @return std::array<int, 3> yaw, pitch then roll
     */
    Vector ToEuler() const
    {
        int64_t R23 = m_matrix[1][2];
        int64_t R33 = m_matrix[2][2];
        int64_t R13 = m_matrix[0][2];
        int64_t R12 = m_matrix[0][1];
        int64_t R11 = m_matrix[0][0];

        double alpha = std::atan2(-R23, R33);
        double beta = std::atan2(R13, std::sqrt(1.0 - (R13 * R13)));
        double gamma = std::atan2(-R12, R11);

        return {std::llround(alpha), std::llround(beta), std::llround(gamma)};
    }

    Vector operator*(const Vector& b) const
    {
        return {m_matrix[0][0] * b[0] + m_matrix[0][1] * b[1]
                    + m_matrix[0][2] * b[2],
                m_matrix[1][0] * b[0] + m_matrix[1][1] * b[1]
                    + m_matrix[1][2] * b[2],
                m_matrix[2][0] * b[0] + m_matrix[2][1] * b[1]
                    + m_matrix[2][2] * b[2]};
    }
};

Vector operator+(const Vector& a, const Vector& b)
{
    return {
        a[0] + b[0],
        a[1] + b[1],
        a[2] + b[2],
    };
}

Vector operator+(const Vector& a) { return a; }

Vector& operator+=(Vector& a, const Vector& b)
{
    a = a + b;
    return a;
}

Vector operator-(const Vector& a) { return {-a[0], -a[1], -a[2]}; }

Vector operator-(const Vector& a, const Vector& b) { return a + -b; }

Vector& operator*=(Vector& vec, const Rotation& rot)
{
    vec = rot * vec;
    return vec;
}

const std::array<Rotation, 24> rotations{
    // Forward
    Rotation(0, 0, 0),
    Rotation(0, 0, 90),
    Rotation(0, 0, 180),
    Rotation(0, 0, -90),
    // Up
    Rotation(0, 90, 0),
    Rotation(0, 90, 90),
    Rotation(0, 90, 180),
    Rotation(0, 90, -90),
    // Down
    Rotation(0, -90, 0),
    Rotation(0, -90, 90),
    Rotation(0, -90, 180),
    Rotation(0, -90, -90),
    // Right
    Rotation(90, 0, 0),
    Rotation(90, 0, 90),
    Rotation(90, 0, 180),
    Rotation(90, 0, -90),
    // Left
    Rotation(-90, 0, 0),
    Rotation(-90, 0, 90),
    Rotation(-90, 0, 180),
    Rotation(-90, 0, -90),
    // Back
    Rotation(180, 0, 0),
    Rotation(180, 0, 90),
    Rotation(180, 0, 180),
    Rotation(180, 0, -90),
};

using Scanner = std::vector<Vector>;
using Scanners = std::vector<Scanner>;

std::ostream& operator<<(std::ostream& os, const Vector& vec)
{
    os << vec[0];
    for (size_t i = 1; i < vec.size(); i++)
        os << "," << vec[i];
    return os;
}

std::ostream& operator<<(std::ostream& os, const Scanner& scanner)
{
    for (const auto& vec : scanner)
        std::cout << vec << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Scanners& scanners)
{
    int scannerId = 0;
    for (const auto& scanner : scanners)
    {
        os << "--- scanner " << scannerId++ << " ---"
           << "\n";
        os << scanner << "\n";
    }
    return os;
}

Scanner operator*(const Scanner& scanner, const Rotation& rot)
{
    Scanner newScanner = scanner;

    for (Vector& vec : newScanner)
    {
        vec *= rot;
    }

    return scanner;
}

Scanner& operator*=(Scanner& scanner, const Rotation& rot)
{
    scanner = scanner * rot;
    return scanner;
}

Scanner operator+(const Scanner& scanner, const Vector& vecB)
{
    Scanner newScanner = scanner;

    for (Vector& vecA : newScanner)
    {
        vecA += vecB;
    }

    return newScanner;
}

Scanner& operator+=(Scanner& scanner, const Vector& vec)
{
    scanner = scanner + vec;
    return scanner;
}

Scanner& operator-=(Scanner& scanner, const Vector& vec)
{
    scanner += -vec;
    return scanner;
}

/*
================================================================================
                            Function Definitions
================================================================================
*/

Scanners CreateScannerData(const std::string& text)
{
    Scanners scanners;
    auto scannerTextBlocks = Split(text, "\n\n");
    for (int i = 0; i < scannerTextBlocks.size(); i++)
    {
        Scanner scanner;
        auto lines = SplitLines(scannerTextBlocks[i]);
        lines.erase(lines.begin());

        for (const auto& line : lines)
        {
            auto num = Split(line, ",");
            scanner.push_back({
                std::stoi(num[0]),
                std::stoi(num[1]),
                std::stoi(num[2]),
            });
        }
        scanners.push_back(scanner);
    }

    return scanners;
}

int64_t GetManhattanDistance(const Vector& a, const Vector& b)
{
    Vector c = b - a;
    return std::abs(c[0]) + std::abs(c[1]) + std::abs(c[2]);
}

/**
 * @brief Solve part 1
 *
 * For each scanner other than 0, rotate each direction. For each direction,
 * translate to all positions. If number of vectors that match >= 12. Stop
 * and save rotation and translation. If none are found, continue to try
 * next scanner. After done with 0, try 1 etc.
 *
 * @param scanners Input data
 * @return long int Amount of beacons found by all scanners
 */
int64_t Part1(const Scanners& scanners)
{
    auto t = Timer();
    std::vector<std::map<std::pair<Vector, Vector>, int64_t>> scannerDistances;
    scannerDistances.reserve(scanners.size());

    for (size_t i = 0; i < scanners.size(); i++)
    {
        std::map<std::pair<Vector, Vector>, int64_t> distances;
        for (const auto& vecA : scanners[i])
        {
            for (const auto& vecB : scanners[i])
            {
                if (vecA == vecB)
                    continue;
                auto key = std::make_pair(std::min(vecA, vecB),
                                          std::max(vecA, vecB));
                if (distances.count(key))
                    continue;

                distances[key] = GetManhattanDistance(vecA, vecB);
            }
        }
        scannerDistances.push_back(distances);
    }

    std::unordered_map<int64_t, int64_t> counter;
    for (const auto& scanner : scannerDistances)
    {
        for (const auto& [key, val] : scanner)
        {
            counter[val]++;
            const auto& [vecA, vecB] = key;
        }
    }

    std::map<std::pair<int64_t, int64_t>,
             std::vector<std::pair<Vector, Rotation>>>
        transforms;

    for (size_t i = 0; i < scanners.size(); i++)
    {
        for (size_t j = i; j < scanners.size(); j++)
        {
            if (i == j)
                continue;

            for (const auto& [keyA, valA] : scannerDistances[i])
            {
                for (const auto& [keyB, valB] : scannerDistances[j])
                {
                    if (valA != valB)
                        continue;

                    const auto& [vecA1, vecA2] = keyA;
                    const auto& [vecB1, vecB2] = keyB;

                    const auto vecA = vecA2 - vecA1;

                    for (const auto& rotation : rotations)
                    {
                        auto vecB = vecB2 - vecB1;
                        vecB *= rotation;

                        if (vecA != vecB)
                            continue;

                        Scanner scannerA = scanners[i];
                        Scanner scannerB = scanners[j];

                        scannerB -= vecB1;
                        scannerB *= rotation;
                        scannerB += vecA1;

                        std::sort(scannerA.begin(), scannerA.end());
                        std::sort(scannerB.begin(), scannerB.end());

                        // std::cout << "VecA: [" << vecA1 << "], [" << vecA2
                        //           << "] = [" << vecA << "]\n";
                        // std::cout << "VecB: [" << vecB1 << "], [" << vecB2
                        //           << "] = [" << vecB << "]\n";

                        // std::cout << "Scanner A:\n" << scannerA << "\n";
                        // std::cout << "Scanner B:\n" << scannerB << "\n";

                        Scanner scannerIntersection;
                        std::set_intersection(
                            scannerA.begin(), scannerA.end(), scannerB.begin(),
                            scannerB.end(),
                            std::back_inserter(scannerIntersection));

                        if (scannerIntersection.size() >= 12)
                            transforms[{i, j}].push_back({vecA, rotation});
                    }
                }
            }
        }
    }

    int64_t count = 0;
    for (const auto& [key, val] : transforms)
        count += val.size();

    return transforms.size();
}

/**
 * @brief Day 19 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day19(const char* fileName)
{
    const std::string text = ReadTextFile(fileName);
    auto scanners = CreateScannerData(text);

    // std::cout << scanners << "\n";

    std::cout << "Part 1:\n" << Part1(scanners) << "\n";
    // 564 too high
    // 142 too low

    // std::cout << "Part 2: " << Part2() << "\n";
}
