#ifndef CRANE_H
#define CRANE_H

#include <string>

template <typename T>
class Crane
{
protected:
    std::string name;
    int indexAboveStack;

public:
    Crane(const std::string &name) : name(name), indexAboveStack(0) {}

    virtual ~Crane() = default;

    std::string getName() const { return name; }
    void setName(const std::string &newName) { name = newName; }

    int getIndexAboveStack() const { return indexAboveStack; }
    void setIndexAboveStack(int newIndexAboveStack) { indexAboveStack = newIndexAboveStack; }

    virtual T *getHookContent() const = 0;
    virtual void setHookContent(T *newContents) = 0;
};

#endif // CRANE_H
