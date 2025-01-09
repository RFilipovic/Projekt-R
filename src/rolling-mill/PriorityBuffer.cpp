#include <string>
#include <vector>

#include "PriorityBuffer.h"
#include "PriorityContainer.h"

PriorityBuffer::PriorityBuffer(int size, const std::string &name) : PriorityContainerStack(name), size(size)  {}

bool PriorityBuffer::isFull(){
    if(containers.size()>=size){
        return true;
    }
    return false;
}
        
bool PriorityBuffer::push(PriorityContainer &container) {
    if(!isFull()){
        containers.push_back(&container);
        return true;
    }
    return false;
}

bool PriorityBuffer::push_multiple(std::vector<PriorityContainer*> priorityContainers){
    if(priorityContainers.size() + containers.size() > size){
        return false;
    }
    PriorityContainerStack::push_multiple(priorityContainers);
}

int PriorityBuffer::getSize(){
    return size;
}