#include<iostream>
#include <iomanip>

#include "ParsedBuffers.h"

class Printer {
private:
    ParsedBuffers* pb;
    //Hook* hook;
    int NArrivals;
    int NBuffers;
    int NHoldovers;
    int getNumberOfStacksInSameCategory(char c);
    int calculateIndexOfHook();
    int calculateHeight();
    std::string centerText(const std::string& text, int width);
    bool sameCategoryStack(const std::string &stack1,const std::string &stack2);
public:
    Printer(ParsedBuffers &pb /*,Kuka*/);
    ~Printer();
    void printEverything();
};