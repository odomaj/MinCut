/*
    IO.h by Alexander Odom
    CS 447 Assignment 4
*/

#include <string>

#ifndef IO_H_
#define IO_H_

class IO
{
    public:
    IO();
    std::string readGraphvizGraph(const std::string& filename);
};

#endif