#include "Node.h"

Node_t::Node_t()
{
    value = 0;
}

Node_t::Node_t(int value_)
{
    value = value_;
}

Node_t::Node_t(Node_t* node)
{
    value = node -> value;
    for(auto it = (node -> edges).begin(); it != (node -> edges).end(); it++)
    {
        edges.push_back(*it);
    }
}

int Node_t::getValue()
{
    return value;
}

/*
    add edge to list
    ensure edge does not already exist
    returns false if the edge already exists and does nothing
    returns true and adds the edge if the edge doesnot exist
*/
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

/*
    incrememnt cost of an edge
    returns false if edge does not exist
    returns true and increments the cost if the edge exists
*/
bool Node_t::incrementEdge(Node_t* destination, int increment)
{
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        if(destination -> getValue() == it -> node -> getValue())
        {
            it -> cost += increment;
            return true;
        }
    }
    return false;
}

void Node_t::updateEdge(Node_t* destination, int cost)
{
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        if(destination -> getValue() == it -> node -> getValue())
        {
            it -> cost = cost;
            return;
        }
    }
    Edge_t edge;
    edge.node = destination;
    edge.cost = cost;
    edges.push_back(edge);
}

std::list<Edge_t> Node_t::getEdges()
{
    return edges;
}

std::list<CompleteEdge_t> Node_t::getCompleteEdges(Node_t* self)
{
    std::list<CompleteEdge_t> completeEdges;
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        CompleteEdge_t edge;
        edge.cost = it -> cost;
        edge.destination = it -> node;
        edge.source = self;
        completeEdges.push_back(edge);
    }
    return completeEdges;
}

void Node_t::zeroizeEdges()
{
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        it -> cost = 0;
    }
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