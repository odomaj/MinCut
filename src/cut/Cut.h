
#include "../graph/Graph.h"

#ifndef CUT_H_
#define CUT_H_

class Cut
{
    public:
    Cut();
    private:
    Graph_t maxFlow;
    Graph_t currentFlow;
    Graph_t residual;
};

#endif