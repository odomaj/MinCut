
#include "../graph/Graph.h"

#ifndef CUT_H_
#define CUT_H_

typedef struct
{
    int maxFlow;
    Graph_t A;
    Graph_t B;
    Graph_t flow;
} STCut_t;


class Cut
{
    public:
    Cut();
    STCut_t findCut(Graph_t& graph);    
    private:
    Graph_t maxFlow;
    Graph_t currentFlow;
    Graph_t residual;
    bool generateResidual();

};

#endif