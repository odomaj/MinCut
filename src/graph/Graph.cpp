#include "Graph.h"

#include <sstream>
#include <iostream>

Graph_t::Graph_t()
{
    
}

Graph_t::Graph_t(Graph_t* graph)
{
    
    for(auto it = graph -> nodes.begin(); it != graph -> nodes.end(); it++)
    {
        nodes.push_back(new Node_t((*it) -> getValue()));
    }
    std::list<StaticEdge_t> edges = graph -> getEdges();
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        findNode(it -> source) -> addEdge(findNode(it -> destination), it -> cost);
    }
}

Graph_t::~Graph_t()
{
    clear();
}

/*
    Serializes the graph to graphviz format
*/
std::string Graph_t::serialize()
{
    std::ostringstream oss;
    std::list<StaticEdge_t> edges = getEdges();
    oss << "digraph {\n";
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        oss << '\t' << it -> source << " -> " << it -> destination << " [label=\"" << it -> cost << "\"]\n";
    }
    oss << '}';
    return oss.str();
}

/*
    Generates a graph from graphviz format
    returns false if digraph string is not properly formatted, leads to incomplete graph
    returns true and generates all vertexes and edges if digraph string is properly formatted
*/
bool Graph_t::deserialize(const std::string& graphvizString)
{
    clear();
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
    return generateVertices(str) && generateEdges(str);
}

/*
    adds nodes to the graph from digraph model
    returns false if digraph string is not properly formatted, leads to incomplete graph
    returns true and generates all edges if digraph string is properly formatted
*/
bool Graph_t::generateVertices(const std::string& digraph)
{
    std::istringstream iss;
    iss.str(digraph);
    int node;
    while(!(iss >> node).fail())
    {
        bool exists = false;
        for(auto it = nodes.begin(); it != nodes.end(); it++)
        {
            if((*it) -> getValue() == node)
            {
                exists = true;
                break;
            }
        }
        if(!exists)
        {
            nodes.push_back(new Node_t(node));
        }
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
        if((*it) -> getValue() > maxValue)
        {
            maxValue = (*it) -> getValue();
        }
    }
    nodes.push_back(new Node_t(maxValue + 1));
    return true;
}

/*
    Generate edges a digraph
    Call after generateVertices
    returns false if digraph string is not properly formatted, leads to incomplete graph
    returns true and generates all edges if digraph string is properly formatted
*/
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
        CompleteEdge_t edge;
        edge.source = findNode(node1);
        edge.destination = findNode(node2);
        edge.cost = stoi(str.substr(start, end-start));
        if(!addEdge(edge))
        {
            return false;
        }
    }
    return true;
}

/*
    Attempts to add all edges in edges
    if any addEdge fails, returns false and stops adding edges
    otherwise adds all edges and returns true
*/
bool Graph_t::addEdges(const std::list<CompleteEdge_t>& edges)
{
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        if(!addEdge(*it))
        {
            return false;
        }
    }
    return true;
}

/*
    Adds an edge to the graph
    Checks to ensure start and end positions exist
    returns false if start and end positions do not exist and does nothing
    returns false if edge already exist and does nothing
    returns  true and add edge otherwise
*/
bool Graph_t::addEdge(CompleteEdge_t edge)
{
    auto it1 = nodes.begin();
    auto it2 = nodes.begin();
    while((*it1) -> getValue() != edge.source -> getValue())
    {
        if(it1++ == nodes.end())
        {
            return false;
        }
    }
    while((*it2) -> getValue() != edge.destination -> getValue())
    {
        if(it2++ == nodes.end())
        {
            return false;
        }
    }
    return (*it1) -> addEdge(*it2, edge.cost);
}

/*
    Increments edge on the graph
    Checks to ensure start and end positions exist
    returns false if start and end positions do not exist and does nothing
    returns false if edge does not exist and does nothing
    returns true and increments edge otherwise
*/
bool Graph_t::incrementEdge(CompleteEdge_t edge, int increment)
{
    auto it1 = nodes.begin();
    auto it2 = nodes.begin();
    while((*it1) -> getValue() != edge.source -> getValue())
    {
        if(it1++ == nodes.end())
        {
            return false;
        }
    }
    while((*it2) -> getValue() != edge.destination -> getValue())
    {
        if(it2++ == nodes.end())
        {
            return false;
        }
    }
    if((*it1) -> incrementEdge(*it2, increment))
    {
        return true;
    }
    int oldCost = (*it1) -> updateEdge(*it1, 0);
    (*it2) -> incrementEdge(*it1, oldCost - increment);
    return true;
}

/*
    Increments edge on the graph
    Checks to ensure start and end positions exist
    returns false if start and end positions do not exist and does nothing
    returns false if edge does not exist and does nothing
    returns true and increments edge otherwise
*/
bool Graph_t::incrementEdge(int source, int destination, int increment)
{
    auto it1 = nodes.begin();
    auto it2 = nodes.begin();
    while((*it1) -> getValue() != source)
    {
        if(it1++ == nodes.end())
        {
            return false;
        }
    }
    while((*it2) -> getValue() != destination)
    {
        if(it2++ == nodes.end())
        {
            return false;
        }
    }
    if((*it1) -> incrementEdge(*it2, increment))
    {
        return true;
    } 
    int oldCost = (*it1) -> updateEdge(*it1, 0);
    (*it2) -> incrementEdge(*it1, oldCost - increment);
    return true;
    
}

/*
    Increment every edge in path by path.flow
    If an edge is flipped will increment with negative flow
    if it fails on any edge returns false and stops
    otherwise returns true and increment every edge
*/
bool Graph_t::incrementPath(const Path_t& path)
{
    auto it = path.vertices.begin();

    CompleteEdge_t edge;
    edge.source = findNode(*it);
    it++;
    edge.destination = findNode(*it++);
    if(!incrementEdge(edge, path.flow))
    {
        return false;
    }

    while(it != path.vertices.end())
    {
        edge.source = edge.destination;
        edge.destination = findNode(*it);
        if(!incrementEdge(edge, path.flow))
        {
            CompleteEdge_t reverseEdge;
            reverseEdge.source = edge.destination;
            reverseEdge.destination = edge.source;
            if(!incrementEdge(reverseEdge, path.flow * -1))
            {
                return false;
            }
        }
        it++;
    }
    
    return true;
}

/*
    Sets an edge from the node with the value of source to the node with the value of destination
    returns false if no node exists with a value of source or destination and does nothing
    otherwise returns true
*/
bool Graph_t::updateEdge(int source, int destination, int value)
{
    Node_t* sourceNode = findNode(source);
    Node_t* destinationNode = findNode(destination);
    if(sourceNode == nullptr || destinationNode == nullptr)
    {
        return false;
    }
    sourceNode -> updateEdge(destinationNode, value);
    return true;
}

/*
    Find an ST Path from the min node to the max node
    returns the shortest path between these nodes if a path exists
    returns an empty list if no path exists
*/
Path_t Graph_t::findSTPath()
{
    Node_t* max = *nodes.begin();
    Node_t* min = *nodes.begin();

    for(auto it = nodes.begin(); it != nodes.end(); it++)
    {
        if((*it) -> getValue() > max -> getValue())
        {
            max = *it;
        }
        else if((*it) -> getValue() < min -> getValue())
        {
            min = *it;
        }
    }
    std::list<CompleteEdge_t> edges = bfs(min, max);
    Path_t path;
    if(edges.empty())
    {
        return path;
    }
    if(edges.front().source -> getValue() != min -> getValue())
    {
        return path;
    }
    if(edges.back().destination -> getValue() != max -> getValue())
    {
        return path;
    }
    path.flow = edges.front().cost;
    path.vertices.push_back(edges.front().source -> getValue());
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        path.vertices.push_back(it -> destination -> getValue());
        if(it -> cost < path.flow)
        {
            path.flow = it -> cost;
        }
    }
    
    return path;
}

/*
    returns a list of StaticEdge_t's containing every edge in the graph
*/
std::list<StaticEdge_t> Graph_t::getEdges()
{
    std::list<StaticEdge_t> edges;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
    {
        int nodeVal = (*it) -> getValue();
        std::list<Edge_t> nodesEdges = (*it) -> getEdges();
        for(auto it2 = nodesEdges.begin(); it2 != nodesEdges.end(); it2++)
        {
            StaticEdge_t edge;
            edge.source = nodeVal;
            edge.destination = it2 -> node -> getValue();
            edge.cost = it2 -> cost;
            edges.push_back(edge);
        }
    }
    return edges;
}

/*
    Breadth First Search
    Used to find shortest path from start to end
*/
std::list<CompleteEdge_t> Graph_t::bfs(Node_t* start, Node_t* end)
{
    std::map<int, CompleteEdge_t> visited;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
    {
        CompleteEdge_t edge;
        edge.source = nullptr;
        edge.destination = nullptr;
        edge.cost = 0;
        visited.insert({(*it) -> getValue(), edge});
    }
    std::list<CompleteEdge_t> edges = start -> getCompleteEdges(start);
    if(edges.empty())
    {
        return std::list<CompleteEdge_t>();
    }
    while(true)
    {
        CompleteEdge_t edge = edges.front();
        edges.pop_front();
        while(edge.cost == 0)
        {
            if(edges.empty())
            {
                return std::list<CompleteEdge_t>();
            }
            edge = edges.front();
            edges.pop_front();
        }
        if((visited.find(edge.destination -> getValue()) -> second).destination == nullptr)
        {
            visited[edge.destination -> getValue()] = edge;
            if(edge.destination -> getValue() == end -> getValue())
            {
                break;
            }
            
            std::list<CompleteEdge_t> newEdges = edge.destination -> getCompleteEdges(edge.destination);
            edges.splice(edges.end(), newEdges);
        }
        if(edges.empty())
        {
            return std::list<CompleteEdge_t>();
        }
    }
    std::list<CompleteEdge_t> path;
    while(end -> getValue() != start -> getValue())
    {
        CompleteEdge_t edge = visited[end -> getValue()];
        path.push_front(edge);
        end = edge.source;
    }
    
    return path;
}

/*
    empties graph
*/
void Graph_t::clear()
{
    if(nodes.empty())
    {
        return;
    }
    for(auto it = nodes.begin(); it != nodes.end(); it++)
    {
        delete *it;
    }
    nodes.clear();
}

/*
    Set cost of all edges to 0
*/
void Graph_t::zeroizeEdges()
{
    for(auto it = nodes.begin(); it != nodes.end(); it++)
    {
        (*it) -> zeroizeEdges();
    }
}

/*
    return the int value of the highest value node
*/
int Graph_t::getHighestNode()
{
    auto it = nodes.begin();
    int max = (*it) -> getValue();
    while(it != nodes.end())
    {
        int i = (*it++) -> getValue();
        if(i > max)
        {
            max = i;
        }
    }
    return max;
}

/*
    return the int value of the lowest value node
*/
int Graph_t::getLowestNode()
{
    auto it = nodes.begin();
    int min = (*it) -> getValue();
    while(it != nodes.end())
    {
        int i = (*it++) -> getValue();
        if(i < min)
        {
            min = i;
        }
    }
    return min;
}

/*
    returns pointer to node with passed value
    if no node exists with passed value returns nullptr
*/
Node_t* Graph_t::findNode(int value)
{
    for(auto it = nodes.begin(); it != nodes.end(); it++)
    {
        if((*it) -> getValue() == value)
        {
            return *it;
        }
    }
    return nullptr;
}

StaticGraph_t Graph_t::getGraph()
{
    StaticGraph_t graph;
    graph.edges = getEdges();
    graph.vertices = getVertices();
    return graph;
}

std::list<int> Graph_t::getVertices()
{
    std::list<int> values;
    for(auto it = nodes.begin(); it != nodes.end(); it++)
    {
        values.push_back((*it) -> getValue());
    }
    return values;
}

ReachableNodes_t Graph_t::getReachable()
{
    ReachableNodes_t output;
    std::list<Edge_t> edges = findNode(getLowestNode()) -> getEdges();
    
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        output.reachable.push_back(it -> node -> getValue());
    }
    
    while(true)
    {
        bool halt = false;
        Edge_t edge;
        edge.cost = 0;
        while(edge.cost == 0)
        {
            if(edges.empty())
            {
                halt = true;
                break;
            }
            edge = edges.front();
            edges.pop_front();
        }
        if(halt)
        {
            break;
        }
        for(auto it = output.reachable.begin(); it != output.reachable.end(); it++)
        {
            if(*it == edge.node -> getValue())
            {
                halt = true;
                break;
            }
        }
        if(halt)
        {
            break;
        }
        output.reachable.push_back(edge.node -> getValue());
        std::list<Edge_t> newEdges = edge.node -> getEdges();
        edges.splice(edges.end(), newEdges);
    }
    
    for(auto it1 = nodes.begin(); it1 != nodes.end(); it1++)
    {
        bool exists = false;
        for(auto it2 = output.reachable.begin(); it2 != output.reachable.end(); it2++)
        {
            if((*it1) -> getValue() == *it2)
            {
                exists = true;
                break;
            }
        }
        if(!exists)
        {
            output.notReachable.push_back((*it1) -> getValue());
        }
    }

    return output;
}

int Graph_t::getFlow()
{
    int flow = 0;
    int min = getLowestNode();
    Node_t* start = findNode(getLowestNode());
    std::list<Edge_t> edges = start -> getEdges();
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        flow += it -> cost;
    }
    return flow;

}