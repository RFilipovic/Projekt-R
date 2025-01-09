#include <iostream>
#include <string>

#include "Container.h"
#include "PriorityContainer.h"

PriorityContainer::PriorityContainer(const std::string &id, int priority, const std::string &colour)
        : Container(id), priority(priority), colour(colour) {}

void PriorityContainer::displayDetails() const {
        std::cout << id << " " << priority << " " << colour << std::endl;
}

std::string PriorityContainer::getDetails() const{
        return id + " " + std::to_string(priority) + " " + colour;
}