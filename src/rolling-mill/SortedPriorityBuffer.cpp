#include <string>
#include <vector>

#include "SortedPriorityBuffer.h"

SortedPriorityBuffer::SortedPriorityBuffer(int size, const std::string &name) : PriorityBuffer(size, name)  {}
        
bool SortedPriorityBuffer::push(PriorityContainer &container) {
    if(containers.size()!=0){
        auto topContainer = containers.back();
        if(container.getColour()!=topContainer->getColour() || container.getPriority()<topContainer->getPriority()){
            return false;
        }
    }

    PriorityBuffer::push(container);
}

bool SortedPriorityBuffer::push_multiple(std::vector<PriorityContainer*> priorityContainers){
    if(priorityContainers.size() + containers.size() > getSize()){
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
