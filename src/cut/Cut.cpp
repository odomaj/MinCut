#include "Cut.h"

Cut::Cut(){}

STCut_t Cut::findCut(const Graph_t& graph)
{
    maxFlow = Graph_t(graph);
    currentFlow = Graph_t(graph);
    currentFlow.zeroizeEdges();
    generateResidual();

}

void Cut::generateResidual()
{

}