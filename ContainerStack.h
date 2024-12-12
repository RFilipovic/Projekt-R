#ifndef CONTAINERSTACK_H 
#define CONTAINERSTACK_H

#include "Container.h"

class ContainerStack {
public:
    virtual bool push(Container &container);
    Container* pop(); 
    Container* top() const; 
    bool isEmpty(); 
    void printStack();
protected:
    std::vector<Container*> containers;
};

#endif // CONTAINERSTACK_H