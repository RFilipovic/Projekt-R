#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept> 

#include "PriorityContainerStack.h"

PriorityContainerStack::PriorityContainerStack(const std::string &name) : name(name){}

bool PriorityContainerStack::push(PriorityContainer &container) {
    containers.push_back(&container);
    return true;
}

bool PriorityContainerStack::push_multiple(std::vector<PriorityContainer*> priorityContainers){
    for(int i=0;i<priorityContainers.size();i++){
        auto c = priorityContainers.back();
        priorityContainers.pop_back();
        push(*c);
    }

    return true;
}

PriorityContainer* PriorityContainerStack:: pop() {
    if (containers.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    PriorityContainer* temp = containers.back(); 
    containers.pop_back(); 
    return temp;
}

std::vector<PriorityContainer*> PriorityContainerStack::pop_multiple(int howMany){
    if(howMany>containers.size()){
        throw std::out_of_range("Not enough containers on stack as you want to pop");
    }
    else if(howMany<2){
        throw std::out_of_range("Argument cannot be less than 2");
    }

    std::vector<PriorityContainer*> poppedContainers;
    for(int i=0;i<howMany;i++){
        auto c = pop();
        poppedContainers.push_back(c);
    }

    return poppedContainers;
}

PriorityContainer* PriorityContainerStack::top() const {
    if (containers.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return containers.back();
}

bool PriorityContainerStack::isEmpty() {
    return containers.empty();
}

void PriorityContainerStack::printStack(){
    for(const auto& c : containers){
        std::cout << "  ";
        c->displayDetails();
    }
    std::cout << std::endl;
}

int PriorityContainerStack::stackOccupancy(){
    return containers.size();
}

std::string PriorityContainerStack::getName(){
    return name;
}

std::vector<PriorityContainer*> PriorityContainerStack::getContainers(){
    return containers;
}

bool PriorityContainerStack::push_infront(PriorityContainer &container){
    containers.insert(containers.begin(), &container);
    return true;
}