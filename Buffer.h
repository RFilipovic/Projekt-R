#ifndef BUFFER_H
#define BUFFER_H

#include "ContainerStack.h"

class Buffer : public ContainerStack {
public:
    Buffer(int size);
    bool isFull();
    bool push(Container* container) override;
private:
    int size;
};

#endif // BUFFER_H
