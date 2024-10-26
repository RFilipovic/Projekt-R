#ifndef CONTAINERSTACK_H 
#define CONTAINERSTACK_H

#include<memory>
#include <vector>
#include"containers.h"

class ContainerStack {
public:
    virtual bool push(Container* container);
    Container* pop(); 
    Container* top() const; 
    bool isEmpty(); 
    void printStack();
protected:
    std::vector<Container*> containers;
};

#endif // CONTAINERSTACK_H
