#include <iostream>
#include <iomanip>

#include "ParsedBuffers.h"
#include "SingleContainerCrane.h"

class Printer {
private:
    MillBuffers* pb;
    Crane* crane;
    int NArrivals;
    int NBuffers;
    int NHoldovers;
    int getNumberOfStacksInSameCategory(char c);
    int calculateIndexOfHook();
    int calculateHeight();
    std::string centerText(const std::string& text, int width);
    bool sameCategoryStack(const std::string &stack1,const std::string &stack2);
public:
    Printer(MillBuffers &pb , Crane &crane);
    ~Printer();
    void printEverything();
    MillBuffers *getParsedBuffers();
    Crane *getCrane();
};