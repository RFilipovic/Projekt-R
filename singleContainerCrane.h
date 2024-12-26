#ifndef SINGLECONTAINERCRANE_H
#define SINGLECONTAINERCRANE_H

#include "Crane.h"
#include "containers.h"

class SingleContainerCrane : public Crane<Container>
{
private:
    Container *container; // Pokazivač na kontejner

public:
    SingleContainerCrane(const std::string &name)
        : Crane<Container>(name), container(nullptr) {}

    ~SingleContainerCrane() override = default;

    Container *getHookContent() const override
    {
        return container;
    }

    void setHookContent(Container *newContents) override
    {
        container = newContents;
    }
};

#endif // SINGLECONTAINERCRANE_H
