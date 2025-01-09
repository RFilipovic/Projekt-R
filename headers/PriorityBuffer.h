#ifndef PRIORITYBUFFER_H
#define PRIORITYBUFFER_H

#include "PriorityContainerStack.h"

class PriorityBuffer : public PriorityContainerStack {
public:
    PriorityBuffer(int size, const std::string &name);
    bool isFull();
    bool push(PriorityContainer &container) override;
    bool push_multiple(std::vector<PriorityContainer*> priorityContainers);
    int getSize();
private:
    int size;
};

#endif