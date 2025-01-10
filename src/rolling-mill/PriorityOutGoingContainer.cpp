#include <string>
#include <vector>

#include "PriorityOutGoingContainerStack.h"

PriorityOutGoingContainerStack::PriorityOutGoingContainerStack(int size, const std::string &name, std::string colour)
             : SortedPriorityBuffer(size,name), colour(colour) {}

bool PriorityOutGoingContainerStack::push(PriorityContainer &container){
    if(container.getColour()!=colour){
        return false;
    }
    SortedPriorityBuffer::push(container);
}

bool PriorityOutGoingContainerStack::push_multiple(std::vector<PriorityContainer*> priorityContainers){
    if(priorityContainers.size() + containers.size() > size){
        return false;
    }
    //check if containers in vector are all the same colour and sorted
    for(int i=1;i<priorityContainers.size();i++){
        PriorityContainer* former = priorityContainers[i-1];
        PriorityContainer* current = priorityContainers[i];
        if(former->getColour()!=current->getColour() || former->getPriority()<current->getPriority()){
            return false;
        }
    }

    PriorityContainer* lastInVectorFirstToPushOnStack = priorityContainers.back();
    if(!push(*lastInVectorFirstToPushOnStack)){
        return false;
    }
    priorityContainers.pop_back();
    PriorityContainerStack::push_multiple(priorityContainers);
}