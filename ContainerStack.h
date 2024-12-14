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
    int getSize();
protected:
    std::vector<Container*> containers;
};

#endif // CONTAINERSTACK_H