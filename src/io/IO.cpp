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