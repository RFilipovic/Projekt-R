#ifndef ENTRYCONTAINERMILL_H
#define ENTRYCONTAINERMILL_H

#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include "SortedPriorityBuffer.h"
#include "PriorityContainer.h"
#include "Container.h"

class EntryContainerMill : public SortedPriorityBuffer {
private:
    int containerId; 
    int pauseFlag;
public:
    EntryContainerMill();
    void startAutoAddContainers(int iterations, double delayInSeconds);
    void pauseTime();
    void continueTime();
    int &getPauseFlag();
};

#endif // ENTRYCONTAINERMILL_H