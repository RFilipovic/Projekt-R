#ifndef SINGLECONTAINERCRANE_H
#define SINGLECONTAINERCRANE_H

#include "Crane.h"

class SingleContainerCrane : public Crane
{
private:
    void *container; // Pokazivač na kontejner

public:
    // Konstruktor samo s imenom
    SingleContainerCrane(const std::string &name)
        : Crane(name) {}

    // Implementacija apstraktnih metoda
    void *getHookContent() const override
    {
        return container;
    }

    void setHookContent(void *newContents) override
    {
        container = newContents;
    }
};

#endif // SINGLECONTAINERCRANE_H
