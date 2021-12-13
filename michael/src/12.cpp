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
class NodeGraph
{
private:
    std::map<std::string, std::list<std::string>> m_nodes;

    void AddNode(const std::string& name)
    {
        m_nodes.insert(std::make_pair(name, std::list<std::string>()));
    }

    void AddLink(const std::string& from, const std::string& to)
    {
        m_nodes[from].push_back(to);
        m_nodes[to].push_back(from);
    }

public:
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

    int Solve(bool isPart1)
    {
        int numberOfPaths = 0;
        std::stack<std::tuple<std::string, std::set<std::string>, bool>> dfs;
        dfs.emplace("start", std::set<std::string>{"start"}, false);

        while (!dfs.empty())
        {
            auto [currentPos, visitedSmallCaves, visitedTwice] = dfs.top();
            dfs.pop();

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
                    dfs.push(std::make_tuple(node, nextVisitedSmallCaves,
                                             visitedTwice));
                }
                else if (visitedSmallCaves.count(node) && !visitedTwice
                         && (node != "start") && (node != "end") && !isPart1)
                {
                    dfs.push(std::make_tuple(node, visitedSmallCaves, true));
                }
            }
        }
        return numberOfPaths;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const NodeGraph& nodeGraph);
};

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
