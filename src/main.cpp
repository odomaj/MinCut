#include "io/IO.h"
#include "graph/Graph.h"

#include <iostream>

int main()
{
    IO io;
    Graph_t graph;
    std::cout << graph.deserialize(io.readGraphvizGraph("../tests/test2.txt"));
    return 0;
}