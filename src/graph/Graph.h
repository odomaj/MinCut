/*
    Graph.h by Alexander Odom
    CS 447 Assignment 4
*/

#include "Node.h"

#include <list>
#include <string>

#ifndef GRAPH_H_
#define GRAPH_H_

class Graph_t
{
    public:
    Graph_t();
    Graph_t(const Graph_t& graph);
    bool deserialize(const std::string& graphvizString);
    void clear();
    void zeroizeEdges();
    void addEdge();
    void incrementEdge(Node_t* node, int increment);
    private:
    std::list<Node_t> nodes;
    bool generateVertexes(const std::string& digraph);
    bool generateEdges(const std::string& digraph);
    bool addEdge(int source, int destination, int cost);
    std::list<Edge_t> bfs(Node_t* start, Node_t* end);
};

#endif