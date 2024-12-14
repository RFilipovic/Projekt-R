#include<iostream>

#include "ParsedBuffers.h"

class Printer
{
private:
    ParsedBuffers* pb;
    int NArrivals;
    int NBuffers;
    int NHoldovers;
public:
    Printer(ParsedBuffers &pb /*,Kuka*/);
    ~Printer();
    void printEverything();
    int calculateIndexOfHook();
    bool sameCategoryStack(const std::string &stack1,const std::string &stack2);
};