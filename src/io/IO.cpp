#include "IO.h"

#include <fstream>
#include <sstream>

IO::IO(){}

std::string IO::readGraphvizGraph(const std::string& filename)
{
    std::ifstream in;
    in.open(filename);
    std::ostringstream oss;
    std::string nextLine;
    while(!(std::getline(in, nextLine)).fail())
    {
        oss << nextLine << '\n';
    }
    in.close();
    return oss.str();
}

void IO::writeSTCut(STCut_t& cut, const std::string& graphFileName, const std::string restFileName)
{
    writeGraphvizGraph(cut.flow, graphFileName);
    std::ofstream out;
    out.open(restFileName);
    out << cut.maxFlow << "\nREACHABLE\n{";
    for(auto it = cut.cut.reachable.begin(); it != cut.cut.reachable.end(); it++)
    {
        out << *it;
        if(*it != cut.cut.reachable.back())
        {
            out << ", ";
        }
    }
    out << "}\nNOT REACHABLE\n{";
    for(auto it = cut.cut.notReachable.begin(); it != cut.cut.notReachable.end(); it++)
    {
        out << *it;
        if(*it != cut.cut.notReachable.back())
        {
            out << ", ";
        }
    }
    out << '}' << std::endl;
}

void IO::writeGraphvizGraph(const std::string& graphvizString, const std::string& filename)
{
    std::ofstream out;
    out.open(filename);
    out << graphvizString;
    out.close();
}