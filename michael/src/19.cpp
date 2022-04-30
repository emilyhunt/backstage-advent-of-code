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

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

//#include <eigen/Dense>
//#include <eigen/Geometry>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                    Classes
================================================================================
// */

// class Eigen::Vector3d
// {
// private:
//     // std::array<long int, 3> m_data;
//     Eigen::Vector3d m_data;

// public:
//     Eigen::Vector3d(long int x, long int y, long int z) : m_data{x, y, z} {}
//     Eigen::Vector3d(const std::array<long int, 3>& vec) : m_data(vec) {}
//     Eigen::Vector3d(const Eigen::Vector3d& vec) : m_data(vec) {}

//     // std::array<long int, 3> Get() const { return m_data; }

//     long int operator[](size_t index) const { return m_data[index]; }

//     Eigen::Vector3d operator+(const Eigen::Translation3d& b) const
//     {
//         return Eigen::Vector3d(Eigen::Vector3d(m_data * b));
//     }

//     Eigen::Vector3d& operator+=(const Eigen::Translation3d& b)
//     {
//         m_data = Eigen::Vector3d(m_data * b);
//         return *this;
//     }

//     bool operator==(const Eigen::Vector3d& b) const
//     {
//         return b.isApprox(m_data);
//         // return (b[0] == m_data[0]) && (b[1] == m_data[1])
//         //        && (b[2] == m_data[2]);
//     }

//     friend std::ostream& operator<<(std::ostream& os, const Eigen::Vector3d&
//     vec);
// };

//static double DegToRad(double angle) { return M_PI / 180.0 * angle; }
//
//Eigen::Matrix3d CreateRotation(double yaw, double pitch, double roll)
//{
//    yaw = DegToRad(yaw);
//    pitch = DegToRad(pitch);
//    roll = DegToRad(roll);
//
//    double c1 = std::cos(roll);
//    double c2 = std::cos(pitch);
//    double c3 = std::cos(yaw);
//    double s1 = std::sin(roll);
//    double s2 = std::sin(pitch);
//    double s3 = std::sin(yaw);
//
//    Eigen::Matrix3d m_matrix{
//        {(c2 * c3), (-s2), (c2 * s3)},
//        {(s1 * s3 + c1 * c3 * s2), (c1 * c2), (c1 * s2 * s3 - c3 * s1)},
//        {(c3 * s1 * s2 - c1 * s3), (c2 * s1), (c1 * c3 + s1 * s2 * s3)}};
//    return m_matrix;
//}

// class Rotation
// {
// private:
//     // std::array<std::array<long int, 3>, 3> m_matrix;
//     Eigen::Matrix3d m_matrix;

// public:
//     Rotation() : m_matrix{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}} {}
//     Rotation(std::array<std::array<long int, 3>, 3> matrix) :
//     m_matrix(matrix)
//     {
//     }
//     Rotation(double yaw, double pitch, double roll) : m_matrix()
//     {
//         double c1 = std::cos(roll);
//         double c2 = std::cos(pitch);
//         double c3 = std::cos(yaw);
//         double s1 = std::sin(roll);
//         double s2 = std::sin(pitch);
//         double s3 = std::sin(yaw);

//         Eigen::Matrix3d m_matrix{
//             {(c2 * c3), (-s2), (c2 * s3)},
//             {(s1 * s3 + c1 * c3 * s2), (c1 * c2), (c1 * s2 * s3 - c3 * s1)},
//             {(c3 * s1 * s2 - c1 * s3), (c2 * s1), (c1 * c3 + s1 * s2 * s3)}};
//     }

//     /**
//      * @brief Construct euler angles from internal rotation matrix
//      *
//      * https://en.wikipedia.org/wiki/Euler_angles
//      * @return std::array<int, 3> yaw, pitch then roll
//      */
//     Eigen::Vector3d ToEuler() const
//     {
//         return m_matrix.eulerAngles(0, 1, 2);
//         // double R23 = m_matrix[1][2];
//         // double R33 = m_matrix[2][2];
//         // double R13 = m_matrix[0][2];
//         // double R12 = m_matrix[0][1];
//         // double R11 = m_matrix[0][0];

//         // double alpha = std::atan2(-R23, R33);
//         // double beta = std::atan2(R13, std::sqrt(1.0 - (R13 * R13)));
//         // double gamma = std::atan2(-R12, R11);

//         // return {std::lround(alpha), std::lround(beta),
//         std::lround(gamma)};
//     }

//     // Eigen::Vector3d operator*(const Eigen::Vector3d& b) const
//     // {
//     //     return m_matrix * b;
//     // }
// };

// std::ostream& operator<<(std::ostream& os, const Eigen::Vector3d& vec)
// {
//     os << vec[0];
//     for (size_t i = 1; i < 3; i++)
//         os << ", " << vec[i];
//     return os;
// }
//
//std::vector<Eigen::Matrix3d> rotations{
//    // Forward
//    CreateRotation(0, 0, 0),
//    CreateRotation(0, 0, 90),
//    CreateRotation(0, 0, 180),
//    CreateRotation(0, 0, -90),
//    // Up
//    CreateRotation(0, 90, 0),
//    CreateRotation(0, 90, 90),
//    CreateRotation(0, 90, 180),
//    CreateRotation(0, 90, -90),
//    // Down
//    CreateRotation(0, -90, 0),
//    CreateRotation(0, -90, 90),
//    CreateRotation(0, -90, 180),
//    CreateRotation(0, -90, -90),
//    // Right
//    CreateRotation(90, 0, 0),
//    CreateRotation(90, 0, 90),
//    CreateRotation(90, 0, 180),
//    CreateRotation(90, 0, -90),
//    // Left
//    CreateRotation(-90, 0, 0),
//    CreateRotation(-90, 0, 90),
//    CreateRotation(-90, 0, 180),
//    CreateRotation(-90, 0, -90),
//    // Back
//    CreateRotation(180, 0, 0),
//    CreateRotation(180, 0, 90),
//    CreateRotation(180, 0, 180),
//    CreateRotation(180, 0, -90),
//};
//
//using Scanners = std::vector<std::vector<Eigen::Vector3d>>;

/*
================================================================================
                            Function Definitions
================================================================================
*/
//
//namespace std
//{
///**
// * @brief Hash function for Vector3d
// */
//template <>
//struct hash<Eigen::Vector3d>
//{
//    /**
//     * @brief Call operator for hash object, for use with std::unordered_map
//     *
//     * @param point point object to hash
//     * @return std::size_t hash of object
//     */
//    size_t operator()(const Eigen::Vector3d& vec) const
//    {
//        std::stringstream ss;
//        ss << vec;
//        return std::hash<std::string>{}(ss.str());
//    }
//};
//}
//
//Scanners CreateScannerData(const std::string& text)
//{
//    std::regex scannerRegex(
//        "--- scanner \\d+ ---\n((?:-*\\d+,){2}-*\\d+\\n*)+");
//    std::regex coordRegex("(-*\\d+),(-*\\d+),(-*\\d+)");
//    std::smatch scannerMatch, coordMatch;
//
//    auto beginScanner
//        = std::sregex_iterator(text.begin(), text.end(), scannerRegex);
//    auto end = std::sregex_iterator();
//
//    Scanners scanners;
//
//    int scannerId = 0;
//    for (auto i = beginScanner; i != end; i++)
//    {
//        scannerMatch = *i;
//        scanners.push_back(std::vector<Eigen::Vector3d>());
//        auto coordsStr = scannerMatch.str();
//        auto beginCoord = std::sregex_iterator(coordsStr.begin(),
//                                               coordsStr.end(), coordRegex);
//        // std::cout << "Scanner: " << scannerId << std::endl;
//        for (auto j = beginCoord; j != end; j++)
//        {
//            coordMatch = *j;
//            // std::cout << coordMatch.str() << std::endl;
//            auto coord = Eigen::Vector3d{std::stod(coordMatch[1].str()),
//                                         std::stod(coordMatch[2].str()),
//                                         std::stod(coordMatch[3].str())};
//            scanners[scannerId].push_back(coord);
//        }
//
//        scannerId++;
//    }
//    return scanners;
//}
//
//template<typename T>
//void PrintScannerData(const T& scanner)
//{
//    for (const auto& coord : scanner)
//        std::cout << coord.transpose() << "\n";
//}
//
//void PrintAllScanners(const Scanners& scanners)
//{
//    int scannerId = 0;
//    std::cout << "\nScanner: " << scannerId++ << "\n";
//    for (const auto& scanner : scanners)
//        PrintScannerData(scanner);
//}
//
//std::vector<Eigen::Vector3d>
//RotateVectors(const Eigen::Matrix3d& rotation,
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
//std::vector<Eigen::Vector3d>
//TranslateVectors(const Eigen::Translation3d& translation,
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
//std::unordered_set<Eigen::Vector3d>
//FindIntersectionGroup(const std::vector<Eigen::Vector3d>& vectorsA,
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
//std::unordered_set<Eigen::Vector3d> Part1(const Scanners& scanners)
//{
//    std::unordered_map<int, std::pair<Eigen::Vector3d, Eigen::Matrix3d>>
//        scannerMap;
//
//    std::unordered_set<Eigen::Vector3d> matches;
//    for (size_t vectorAIdx = 0; vectorAIdx < scanners.size(); vectorAIdx++)
//    {
//        for (size_t vectorBIdx = 0; vectorBIdx < scanners.size(); vectorBIdx++)
//        {
//            if (vectorAIdx == vectorBIdx)
//                continue;
//            auto currentMatches = FindIntersectionGroup(scanners[vectorAIdx],
//                                                        scanners[vectorBIdx]);
//            matches.insert(currentMatches.begin(), currentMatches.end());
//        }
//    }
//
//    return matches;
//}
// 404 -588 -901
// 686 422 578
// -282 -1010 -1479

/**
 * @brief Day 19 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day19(const char* fileName)
{
    //const std::string text = ReadTextFile(fileName);
    //auto scannerData = CreateScannerData(text);
    //// PrintAllScanners(scannerData);

    //// Scanners test = {{
    ////     {1, 0, 0},  {-1, 0, 0},  {0, 1, 0},   {1, 1, 0},   {-1, 1, 0},
    ////     {0, -1, 0}, {1, -1, 0},  {-1, -1, 0}, {0, 0, 1},   {1, 0, 1},
    ////     {-1, 0, 1}, {0, 1, 1},   {1, 1, 1},   {-1, 1, 1},  {0, -1, 1},
    ////     {1, -1, 1}, {-1, -1, 1}, {0, -1, -1}, {1, -1, -1}, {-1, -1, -1},
    //// }};

    //auto matches = Part1(scannerData);

    //PrintScannerData(matches);

    //// PrintVector(matches, "\n\n");

    std::cout << "Part 1: " << "\n";
    std::cout << "Part 2: " << "\n";

    // PrintAllScanners(test);
    // test[0] = RotateVectors(rotations[1], test[0]);
    // PrintAllScanners(test);
}
