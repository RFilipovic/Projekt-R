#ifndef OUTGOINGCONTAINERSTACK_H
#define OUTGOINGCONTAINERSTACK_H

#include <iostream>
#include <string>
#include <chrono>
#include "ContainerStack.h"

class OutgoingContainerStack : public ContainerStack {
private:
    bool& pauseFlag; // Reference to the shared pause flag

public:
    // Constructor accepting a reference to the shared pause flag
    OutgoingContainerStack(bool& sharedPauseFlag);

    // Method to pop containers from the stack every 5 minutes
    void startPoppingContainers(double popDelayInMinutes);
};

#endif // OUTGOINGCONTAINERSTACK_H
