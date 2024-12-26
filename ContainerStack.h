#ifndef CONTAINERSTACK_H 
#define CONTAINERSTACK_H

#include "Container.h"

class ContainerStack {
public:
    ContainerStack(const std::string &name);
    virtual bool push(Container &container);
    Container* pop(); 
    Container* top() const; 
    bool isEmpty(); 
    void printStack();
    int stackOccupancy();
    std::string getName();
    std::vector<Container*> getContainers();
protected:
    std::string name;
    std::vector<Container*> containers;
};

#endif // CONTAINERSTACK_H