/*
    Graph.h by Alexander Odom
    CS 447 Assignment 4
*/

#include "Node.h"

#include <list>
#include <string>
#include <map>

#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct
{
    std::list<int> vertices;
    int flow;
} Path_t;

typedef struct
{
    int source;
    int destination;
    int cost;
} StaticEdge_t;

typedef struct
{
    std::list<int> vertices;
    std::list<StaticEdge_t> edges;
} StaticGraph_t;

typedef struct
{
    std::list<int> reachable;
    std::list<int> notReachable;
} ReachableNodes_t;

class Graph_t
{
    public:
    Graph_t();
    Graph_t(Graph_t* graph);
    ~Graph_t();
    std::string serialize();
    bool deserialize(const std::string& graphvizString);
    void clear();
    void zeroizeEdges();
    bool addEdges(const std::list<CompleteEdge_t>& edges);
    bool incrementEdge(CompleteEdge_t edge, int increment);
    bool incrementEdge(int source, int destination, int increment);
    Path_t findSTPath();
    bool incrementPath(const Path_t& path);
    bool updateEdge(int source, int destination, int value);
    StaticGraph_t getGraph();
    std::list<StaticEdge_t> getEdges();
    int getHighestNode();
    int getLowestNode();
    std::list<int> getVertices();
    ReachableNodes_t getReachable();
    int getFlow();
    private:
    std::list<Node_t*> nodes;
    bool generateVertices(const std::string& digraph);
    bool generateEdges(const std::string& digraph);
    int findMaxEdge(const std::string& digraph);
    bool addEdge(CompleteEdge_t edge);
    Node_t* findNode(int value);
    std::list<CompleteEdge_t> bfs(Node_t* start, Node_t* end);
};

#endif