/**
 * @file 12.cpp
 * @author Michael Otty (michael.otty@gmail.com)
 * @brief Advent of Code 2021 day 12
 * @version 1.0.0
 * @date 2021-12-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <tuple>

#include "Days.h"
#include "Utilities.h"

/*
================================================================================
                                Classes
================================================================================
*/
/**
 * @brief Node graph implemented as a map of lists
 *
 */
class NodeGraph
{
private:
    /// Map of nodes on the graph
    std::map<std::string, std::list<std::string>> m_nodes;

    /**
     * @brief Add a node to the node graph, if it's not unique then is overidden
     *
     * @param name or ID of the node
     */
    void AddNode(const std::string& name)
    {
        m_nodes.insert(std::make_pair(name, std::list<std::string>()));
    }

    /**
     * @brief Add a link between nodes
     *
     * @param from First node
     * @param to Second node
     */
    void AddLink(const std::string& from, const std::string& to)
    {
        m_nodes[from].push_back(to);
        m_nodes[to].push_back(from);
    }

public:
    /**
     * @brief Construct a new Node Graph object
     *
     * @param fileText text file used to create data structure
     */
    NodeGraph(const std::string& fileText)
    {
        std::set<std::string> nodeNames;
        std::vector<std::pair<std::string, std::string>> links;

        std::regex regex("(\\w+)-(\\w+)");
        std::smatch match;
        auto begin
            = std::sregex_iterator(fileText.begin(), fileText.end(), regex);
        auto end = std::sregex_iterator();

        for (auto i = begin; i != end; i++)
        {
            match = *i;
            nodeNames.insert(match[1].str());
            nodeNames.insert(match[2].str());
            links.push_back(std::make_pair(match[1].str(), match[2].str()));
        }

        for (const auto& name : nodeNames)
            AddNode(name);

        for (const auto& [left, right] : links)
            AddLink(left, right);
    }

    /**
     * @brief Solve part 1 or part 2
     *
     * @param isPart1 set to true to solve part 1 otherwise part 2 is solved
     * @return int Solution
     */
    int Solve(bool isPart1)
    {
        int numberOfPaths = 0;
        std::stack<std::tuple<std::string, std::set<std::string>, bool>>
            frontier;
        frontier.emplace("start", std::set<std::string>{"start"}, false);

        while (!frontier.empty())
        {
            auto [currentPos, visitedSmallCaves, visitedTwice] = frontier.top();
            frontier.pop();

            if (currentPos == "end")
            {
                numberOfPaths++;
                continue;
            }

            for (const auto& node : m_nodes[currentPos])
            {
                if (!visitedSmallCaves.count(node))
                {
                    std::set<std::string> nextVisitedSmallCaves;
                    for (const auto& item : visitedSmallCaves)
                        nextVisitedSmallCaves.insert(item);

                    std::string lowerName = node;
                    std::transform(node.begin(), node.end(), lowerName.begin(),
                                   [](unsigned char c)
                                   { return std::tolower(c); });

                    if (lowerName == node)
                        nextVisitedSmallCaves.insert(node);
                    frontier.push(std::make_tuple(node, nextVisitedSmallCaves,
                                                  visitedTwice));
                }
                else if (visitedSmallCaves.count(node) && !visitedTwice
                         && (node != "start") && (node != "end") && !isPart1)
                {
                    frontier.push(
                        std::make_tuple(node, visitedSmallCaves, true));
                }
            }
        }
        return numberOfPaths;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const NodeGraph& nodeGraph);
};

/**
 * @brief Output stream override for NodeGraph class
 *
 * @param os Output stream, will be modified by reference
 * @param nodeGraph Node graph to output
 * @return std::ostream& Reference to modified output stream
 */
std::ostream& operator<<(std::ostream& os, const NodeGraph& nodeGraph)
{
    for (const auto& baseNode : nodeGraph.m_nodes)
    {
        os << baseNode.first << ": ";
        for (const auto& node : baseNode.second)
            os << node << ", ";
        os << "\n";
    }

    return os;
}

/*
================================================================================
                            Function Definitions
================================================================================
*/
/**
 * @brief Day 12 of Advent of Code
 *
 * @param fileName to read as puzzle input
 */
void Day12(const char* fileName)
{
    const std::string text = ReadTextFile(fileName);
    NodeGraph nodeGraph(text);

    std::cout << "Part 1: " << nodeGraph.Solve(true) << "\n";
    std::cout << "Part 2: " << nodeGraph.Solve(false) << "\n";
}
