#ifndef CRANE_H
#define CRANE_H

#include <string>

class Crane
{
protected:
    std::string name;
    int indexAboveStack;

public:
    Crane(const std::string &name);

    virtual ~Crane() = default;

    std::string getName() const;
    void setName(const std::string &newName);

    int getIndexAboveStack() const;
    void setIndexAboveStack(int newIndexAboveStack);

    // Apstraktne metode za sadržaj kuke
    virtual void *getHookContent() const = 0;
    virtual void setHookContent(void *newContents) = 0;
};

#endif
