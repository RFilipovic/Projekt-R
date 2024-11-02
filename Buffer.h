#ifndef BUFFER_H
#define BUFFER_H

#include "ContainerStack.h"

class Buffer : public ContainerStack {
public:
    Buffer(int size, const std::string &name);
    bool isFull();
    bool push(Container &container) override;
private:
    int size;
    std::string name;
};

#endif // BUFFER_H