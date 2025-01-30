#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include "EntryContainerMill.h"

EntryContainerMill::EntryContainerMill() : containerId(1), SortedPriorityBuffer(20, "A0") {
    pauseTime();
}

void EntryContainerMill::pauseTime(){
    pauseFlag = 1;
}

void EntryContainerMill::continueTime(){
    pauseFlag = 0;
}

void EntryContainerMill::startAutoAddContainers(int iterations, double delayInSeconds) {
    for (int i = 0; i < iterations; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        while (elapsed.count() < delayInSeconds) {
            if(pauseFlag == 0){
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            }
        }

        int containerId = std::rand() % 100 + 1;
        int randPriority = std::rand() % 25 + 1;
        int randNumber = std::rand() % 2;

        std::string contColour;

        if(randNumber == 0){
            contColour = "B";
        }
        else{
            contColour = "V";
        }

        std::string name = "B";
        name.append(std::to_string(containerId));


        PriorityContainer* newContainer = new PriorityContainer(name, randPriority, contColour);

        push(*newContainer);
    }
}

int &EntryContainerMill::getPauseFlag(){
    return pauseFlag;
}