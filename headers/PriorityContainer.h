#ifndef PRIORITYCONTAINER_H
#define PRIORITYCONTAINER_H

#include "Container.h"

class PriorityContainer : public Container {
public:
    PriorityContainer(const std::string &id, int priority, const std::string &colour);
    void displayDetails() const;
    std::string getDetails() const;
    int getPriority();
    std::string getColour();
private:
    int priority;
    std::string colour;
};

#endif //PRIORITYCONTAINER_H