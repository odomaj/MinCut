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
    Cut cut;
    STCut_t stCut = cut.findCut(graph);
    io.writeSTCut(stCut, "../tests/test2Flow.txt", "../tests/test2Rest.txt");
    return 0;
}