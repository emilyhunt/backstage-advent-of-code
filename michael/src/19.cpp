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
#include <initializer_list>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                    Classes
================================================================================
*/

using Vector = std::array<int64_t, 3>;

Vector operator+(const Vector& a, const Vector& b)
{
    return {
        a[0] + b[0],
        a[1] + b[1],
        a[2] + b[2],
    };
}

Vector& operator+=(Vector& a, const Vector& b)
{
    a = a + b;
    return a;
}

static double DegToRad(double angle) { return M_PI / 180.0 * angle; }

class Rotation
{
private:
    std::array<std::array<int64_t, 3>, 3> m_matrix;

public:
    Rotation() : m_matrix{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}} {}

    // Rotation(std::initializer_list<std::array<int64_t, 3>> matrix)
    //     : m_matrix(matrix)
    //{
    // }

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

//}
//
// std::vector<Eigen::Vector3d>
// RotateVectors(const Eigen::Matrix3d& rotation,
//              const std::vector<Eigen::Vector3d>& vectors)
//{
//    std::vector<Eigen::Vector3d> rotatedVectors(vectors);
//    for (auto& vector : rotatedVectors)
//    {
//        vector = rotation * vector;
//    }
//    return rotatedVectors;
//}
//
// std::vector<Eigen::Vector3d>
// TranslateVectors(const Eigen::Translation3d& translation,
//                 const std::vector<Eigen::Vector3d>& vectors)
//{
//    std::vector<Eigen::Vector3d> translatedVectors(vectors);
//    for (auto& vector : translatedVectors)
//    {
//        vector = translation * vector;
//    }
//    return translatedVectors;
//}
//
// std::unordered_set<Eigen::Vector3d>
// FindIntersectionGroup(const std::vector<Eigen::Vector3d>& vectorsA,
//                      const std::vector<Eigen::Vector3d>& vectorsB)
//{
//    for (const auto& rotation : rotations)
//    {
//        auto rotatedVecs = RotateVectors(rotation, vectorsB);
//        for (const auto& vecB : rotatedVecs)
//        {
//            for (const auto& vecA : vectorsA)
//            {
//                Eigen::Translation3d translate(vecA - vecB);
//                std::vector<Eigen::Vector3d> transfVecs
//                    = TranslateVectors(translate, rotatedVecs);
//                std::unordered_set<Eigen::Vector3d> currentMatches;
//
//                for (const auto& originalVec : vectorsA)
//                {
//                    for (const auto& transfVec : transfVecs)
//                    {
//                        if (transfVec.isApprox(originalVec, 0.1))
//                        {
//                            currentMatches.insert(transfVec);
//                            break;
//                        }
//                    }
//                }
//
//                if (currentMatches.size() >= 12)
//                {
//                    return currentMatches;
//                }
//            }
//        }
//    }
//    return std::unordered_set<Eigen::Vector3d>();
//}

// 564 too high
// 142 too low

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
    // std::unordered_map<int, std::pair<Vector3d, Matrix3d>>
    //     scannerMap;

    // std::unordered_set<Eigen::Vector3d> matches;
    // for (size_t vectorAIdx = 0; vectorAIdx < scanners.size(); vectorAIdx++)
    //{
    //     for (size_t vectorBIdx = 0; vectorBIdx < scanners.size();
    //     vectorBIdx++)
    //     {
    //         if (vectorAIdx == vectorBIdx)
    //             continue;
    //         auto currentMatches = FindIntersectionGroup(scanners[vectorAIdx],
    //                                                     scanners[vectorBIdx]);
    //         matches.insert(currentMatches.begin(), currentMatches.end());
    //     }
    // }

    return 0;
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

    std::cout << scanners << "\n";

    std::cout << "Part 1: " << Part1(scanners) << "\n";
    // std::cout << "Part 2: " << Part2() << "\n";
}
