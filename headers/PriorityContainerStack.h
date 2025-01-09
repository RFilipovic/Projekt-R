#ifndef PRIORITYCONTAINERSTACK_H 
#define PRIORITYCONTAINERSTACK_H

#include <vector>

#include "PriorityContainer.h"

class PriorityContainerStack {
public:
    PriorityContainerStack(const std::string &name);
    virtual bool push(PriorityContainer &container);
    virtual bool push_multiple(std::vector<PriorityContainer*> priorityContainers);
    PriorityContainer* pop(); 
    std::vector<PriorityContainer*> pop_multiple(int howMany);
    PriorityContainer* top() const; 
    bool isEmpty(); 
    void printStack();
    int stackOccupancy();
    std::string getName();
    std::vector<PriorityContainer*> getContainers();
    bool push_infront(PriorityContainer &container);
protected:
    std::string name;
    std::vector<PriorityContainer*> containers;
};

#endif