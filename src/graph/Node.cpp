#include "Node.h"

Node_t::Node_t()
{
    value = 0;
}

Node_t::Node_t(int value_)
{
    value = value_;
}

int Node_t::getValue()
{
    return value;
}

bool Node_t::addEdge(Node_t* node, int cost)
{
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        if(node -> getValue() == it -> node -> getValue())
        {
            return false;
        }
    }
    Edge_t edge;
    edge.node = node;
    edge.cost = cost;
    edges.push_back(edge);
    return true;
}

bool operator<(Node_t node1, Node_t node2)
{
    return node1.getValue() < node2.getValue();
}

bool operator>(Node_t node1, Node_t node2)
{
    return node1.getValue() > node2.getValue();
}

bool operator==(Node_t node1, Node_t node2)
{
    return node1.getValue() == node2.getValue();
}