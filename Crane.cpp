#include "Crane.h"

Crane::Crane(const std::string &name)
    : name(name), indexAboveStack(0) {}

std::string Crane::getName() const
{
    return name;
}

void Crane::setName(const std::string &newName)
{
    name = newName;
}

int Crane::getIndexAboveStack() const
{
    return indexAboveStack;
}

void Crane::setIndexAboveStack(int newIndexAboveStack)
{
    indexAboveStack = newIndexAboveStack;
}
