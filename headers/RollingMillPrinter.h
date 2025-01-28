#include <iostream>
#include <iomanip>

#include "MillBuffers.h"
#include "SingleContainerCrane.h"

class RollingMillPrinter {
private:
    MillBuffers* mb;
    Crane* c1;
    Crane* c2;
    int NArrivals;
    int NBuffers;
    int NSortedBuffers;
    int NHoldovers;
    int getNumberOfStacksInSameCategory(char c);
    int calculateIndexOfCrane(Crane &crane);
    int calculateHeight();
    std::string centerText(const std::string& text, int width);
    bool sameCategoryStack(const std::string &stack1,const std::string &stack2);
public:
    RollingMillPrinter(MillBuffers &mb, Crane &c1, Crane &c2);
    ~RollingMillPrinter();
    void printEverything();
    MillBuffers *getMillBuffers();
    Crane *getC1();
    Crane *getC2();
};