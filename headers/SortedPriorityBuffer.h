#ifndef SORTEDPRIORITYBUFFER_H
#define SORTEDPRIORITYBUFFER_H

#include "PriorityBuffer.h"

class SortedPriorityBuffer : public PriorityBuffer {
public:
    SortedPriorityBuffer(int size, const std::string &name);
    bool push(PriorityContainer &container);
    bool push_multiple(std::vector<PriorityContainer*> priorityContainers);
};

#endif