/*
    IO.h by Alexander Odom
    CS 447 Assignment 4
*/

#include <string>
#include "../cut/Cut.h"

#ifndef IO_H_
#define IO_H_

class IO
{
    public:
    IO();
    std::string readGraphvizGraph(const std::string& filename);
    void writeSTCut(STCut_t& cut, const std::string& graphFileName, const std::string restFileName);
    private:
    void writeGraphvizGraph(const std::string& graphvizString, const std::string& filename);
};

#endif