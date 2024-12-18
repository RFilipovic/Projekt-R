#include "OutgoingContainerStack.h"
#include <chrono>
#include <thread> 

OutgoingContainerStack::OutgoingContainerStack(bool& sharedPauseFlag)
    : pauseFlag(sharedPauseFlag) {}

void OutgoingContainerStack::startPoppingContainers(double popDelayInMinutes) {
    while (!isEmpty()) {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = start;
        std::chrono::duration<double> elapsed = end - start;

        while (elapsed.count() < popDelayInMinutes * 60) {
            if (!pauseFlag) {
                end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
            }
        }

        Container* poppedContainer = pop();
        if (poppedContainer) {
            delete poppedContainer;
        }
    }
}
