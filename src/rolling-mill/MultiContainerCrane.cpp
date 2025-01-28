#include "MultiContainerCrane.h"
#include "ParsedBuffers.h"
#include <iostream>
#include <stdexcept>

void MultiContainerCrane::removeContents()
{
    if (hookContents && !hookContents->empty())
    {
        hookContents->clear();
    }
    else
    {
        throw std::runtime_error("Hook contents are already empty or uninitialized.");
    }
}