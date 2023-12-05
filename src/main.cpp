#include "io/IO.h"
#include "cut/Cut.h"

#include <iostream>

int main()
{
    IO io;
    Graph_t graph;
    if(!graph.deserialize(io.readGraphvizGraph("../tests/test2.txt")))
    {
        std::cout << "[ERROR] Graph not deserialized\n";
        return -1;
    }
    //std::cout << graph.serialize();
    Cut cut;
    cut.findCut(graph);
    std::cout << "still running\n";
    return 0;
}