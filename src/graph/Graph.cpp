#include "Graph.h"

#include <sstream>
#include <iostream>

Graph_t::Graph_t()
{

}

bool Graph_t::deserialize(const std::string& graphvizString)
{
    nodes.clear();
    std::istringstream iss;
    iss.str(graphvizString);
    while(!iss.fail())
    {
        std::string str;
        iss >> str;
        if(str == "digraph")
        {
            iss >> str;
            if(str != "{")
            {
                return false;
            }
            break;
        }
        else if(str == "digraph{")
        {
            break;
        }
    }

    std::ostringstream oss;
    while(!iss.fail())
    {
        std::string str;
        iss >> str;
        if(str == "}")
        {
            break;
        }
        oss << str << ' ';
    }
    std::string str = oss.str();
    return generateVertexes(str) && generateEdges(str);
}

bool Graph_t::generateVertexes(const std::string& digraph)
{
    std::istringstream iss;
    iss.str(digraph);
    int node;
    while(!(iss >> node).fail())
    {
        nodes.push_back(Node_t(node));
        while(iss.get() != ';')
        {
            if(iss.fail())
            {
                return false;
            }
        }
    }
    int maxValue = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
    {
        if(it -> getValue() > maxValue)
        {
            maxValue = it -> getValue();
        }
    }
    nodes.push_back(Node_t(maxValue + 1));
    return true;
}

bool Graph_t::generateEdges(const std::string& digraph)
{
    std::istringstream iss;
    iss.str(digraph);
    int node1;
    while(!(iss >> node1).fail())
    {
        std::string str;
        if((iss >> str).fail())
        {
            return false;
        }
        int node2;
        if((iss >> node2).fail())
        {
            return false;
        }
        if((iss >> str).fail())
        {
            return false;
        }
        int start = 0;
        while(start < str.length())
        {
            if(str[start] == '"')
            {
                break;
            }
            start++;
        }
        start++;
        int end = start;
        while(end < str.length())
        {
            if(str[end] == '"')
            {
                break;
            }
            end++;
        }
        if(!addEdge(node1, node2, stoi(str.substr(start, end-start))))
        {
            return false;
        }
    }
    return true;
}

bool Graph_t::addEdge(int source, int destination, int cost)
{
    auto it1 = nodes.begin();
    auto it2 = nodes.begin();
    while(it1 -> getValue() != source)
    {
        if(it1++ == nodes.end())
        {
            return false;
        }
    }
    while(it2 -> getValue() != destination)
    {
        if(it2++ == nodes.end())
        {
            return false;
        }
    }
    return it1 -> addEdge(&*it2, cost);
}

std::queue<Edge_t> Graph_t::bfs(Node_t* start, Node_t* end)
{
    std::queue<Edge_t> path;
    std::list<Edge_t> edges = start -> getEdges();
    Node_t* node;/*
    while(!edges.empty() && )
    {

    }
    */
    return path;
}