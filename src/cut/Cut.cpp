#include "Cut.h"

#include <iostream>

Cut::Cut(){}

STCut_t Cut::findCut(Graph_t& graph)
{
    maxFlow = Graph_t(graph);
    currentFlow = Graph_t(graph);
    currentFlow.zeroizeEdges();
    int i = 0;
    while(true)
    {
        std::cout << '\n';
        if(!generateResidual())
        {
            STCut_t cut;
            return cut;
        }
        //*
        std::cout << "MAX\n" << maxFlow.serialize() << '\n';
        std::cout << "FLOW\n" << currentFlow.serialize() << '\n';
        std::cout << "RESIDUAL\n" << residual.serialize() << '\n';
        std::cout << "__________________________________________________________________\n";
        //*/
        Path_t path = residual.findSTPath();
        if(path.vertices.empty())
        {
            break;
        }
        //*
        std::cout << "NEXT PATH\n" << path.flow << '\n';
        for(auto it = path.vertices.begin(); it != path.vertices.end(); it++)
        {
            std::cout << *it << "->"; 
        }
        //*/
        currentFlow.incrementPath(path);
    }
    std::cout << maxFlow.serialize() << '\n';
    std::cout << currentFlow.serialize() << '\n';
    STCut_t cut;
    return cut;
}

bool Cut::generateResidual()
{
    residual.clear();
    residual = Graph_t(maxFlow);
    std::list<StaticEdge_t> current = currentFlow.getEdges();
    for(auto it = current.begin(); it != current.end(); it++)
    {
        if(it -> cost == 0)
        {
            continue;
        }
        if(!residual.incrementEdge(it -> source, it -> destination, -1 * (it -> cost)))
        {
            return false;
        }
        residual.updateEdge(it -> destination, it -> source, it -> cost);
    }
    return true;
}