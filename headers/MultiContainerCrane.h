#ifndef MULTICONTAINERCRANE_H
#define MULTICONTAINERCRANE_H

#include "Crane.h"
#include "PriorityContainer.h"
#include <list>

class MultiContainerCrane : public Crane
{
private:
    std::list<PriorityContainer>* hookContents; 

public:
    MultiContainerCrane(const std::string &name, const std::vector<std::string> &stackNames)
        : Crane(name, stackNames) {}

        void* getHookContent() const override
    {
        return this->hookContents;
    }

    void setHookContent(void *newContent) override
    {
        this->hookContents = static_cast<std::list<PriorityContainer>*>(newContent);
    }

    
    void removeContents();
};

#endif