#ifndef PRIORITYOUTGOINGCONTAINERSTACK_H
#define PRIORITYOUTGOINGCONTAINERSTACK_H

#include <iostream>
#include <string>
#include <chrono>
#include "SortedPriorityBuffer.h"

class PriorityOutGoingContainerStack : public SortedPriorityBuffer {
private:
    int pauseFlag;
    std::string colour;

public:
    PriorityOutGoingContainerStack(int size, const std::string &name, std::string colour);
    bool push(PriorityContainer &container);
    bool push_multiple(std::vector<PriorityContainer*> priorityContainers);
    void startPoppingContainers(int popDelay);
    
    void continueTime(){
        pauseFlag = 0;
    };

    void pauseTime(){
        pauseFlag = 1;
    };
};

#endif