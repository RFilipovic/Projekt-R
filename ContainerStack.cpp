#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept> 

#include "ContainerStack.h"

ContainerStack::ContainerStack(const std::string &name) : name(name){}

bool ContainerStack::push(Container &container) {
    containers.push_back(&container);
    return true;
}

Container* ContainerStack:: pop() {
    if (containers.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    Container* temp = containers.back(); 
    containers.pop_back(); 
    return temp;
}

Container* ContainerStack::top() const {
    if (containers.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return containers.back();
}

bool ContainerStack::isEmpty() {
    return containers.empty();
}

void ContainerStack::printStack(){
    for(const auto& c : containers){
        std::cout << "  ";
        c->displayDetails();
    }
    std::cout << std::endl;
}

int ContainerStack::getSize(){
    return containers.size();
}

std::string ContainerStack::getName(){
    return name;
}