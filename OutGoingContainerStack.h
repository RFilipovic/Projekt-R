#ifndef OUTGOINGCONTAINERSTACK_H
#define OUTGOINGCONTAINERSTACK_H

#include <iostream>
#include <string>
#include <chrono>
#include "Buffer.h"

class OutGoingContainerStack : public Buffer {
private:
    int pauseFlag; // Reference to the shared pause flag

public:
    // Constructor accepting a reference to the shared pause flag
    OutGoingContainerStack();

    // Method to pop containers from the stack every 5 minutes
    void startPoppingContainers(int popDelay);

    void continueTime(){
        pauseFlag = 0;
    };

    void pauseTime(){
        pauseFlag = 1;
    };
};

#endif // OUTGOINGCONTAINERSTACK_H
