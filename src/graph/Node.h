/*
    Node.h by Alexander Odom
    CS 447 Assignment 4
*/

#include <list>

#ifndef NODE_H_
#define NODE_H_

class Node_t;

typedef struct
{
    Node_t* node;
    int cost;
} Edge_t;

class Node_t
{
    public:
    Node_t();
    Node_t(int value_);
    int getValue();
    bool addEdge(Node_t* node, int cost);
    std::list<Edge_t> getEdges();
    private:
    int value;
    std::list<Edge_t> edges;
};

bool operator<(Node_t node1, Node_t node2);
bool operator>(Node_t node1, Node_t node2);
bool operator==(Node_t node1, Node_t node2);

#endif