#ifndef ENTRYCONTAINERSTACK_H
#define ENTRYCONTAINERSTACK_H

#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include "ContainerStack.h"
#include "UntilDueContainer.h"

class EntryContainerStack : public ContainerStack {
private:
    int containerId; 
    bool pauseFlag;

public:
    
    EntryContainerStack();

    
    void startAutoAddContainers(int iterations, double delayInSeconds);

    void pauseTime();

    void continueTime();
};

#endif // ENTRYCONTAINERSTACK_H
