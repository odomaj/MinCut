/*
    Graph.h by Alexander Odom
    CS 447 Assignment 4
*/

#include "Node.h"

#include <list>
#include <string>
#include <queue>

#ifndef GRAPH_H_
#define GRAPH_H_

class Graph_t
{
    public:
    Graph_t();
    bool deserialize(const std::string& graphvizString);
    private:
    std::list<Node_t> nodes;
    bool generateVertexes(const std::string& digraph);
    bool generateEdges(const std::string& digraph);
    bool addEdge(int source, int destination, int cost);
    std::queue<Edge_t> bfs(Node_t* start, Node_t* end);
};

#endif