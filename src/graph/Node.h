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
    Node_t* source;
    Node_t* destination;
    int cost;
} CompleteEdge_t;

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
    bool incrementEdge(Node_t* destination, int increment);
    int updateEdge(Node_t* destination, int cost);
    std::list<Edge_t> getEdges();
    std::list<CompleteEdge_t> getCompleteEdges(Node_t* self);
    void zeroizeEdges();
    private:
    int value;
    std::list<Edge_t> edges;
};

bool operator<(Node_t node1, Node_t node2);
bool operator>(Node_t node1, Node_t node2);
bool operator==(Node_t node1, Node_t node2);

#endif