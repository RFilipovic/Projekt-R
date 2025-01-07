#include <iostream>

#include "HotStorageSimulator.h"

int main(){

    ParsedBuffers *data = new ParsedBuffers("ulaz.txt");
    Crane *crane = new SingleContainerCrane("CRANE", data->getStackNames());
    Printer *printer = new Printer(*data, *crane);

    HotStorageSimulator simulator(*printer);

    simulator.simulate();

    return 0;
}

//g++ -g main.cpp ParsedBuffers.cpp InitialStateReader.cpp ContainerStack.cpp Buffer.cpp
//Container.cpp UntilDueContainer.cpp Printer.cpp Crane.cpp HotStorageSimulator.cpp SingleContainerCrane.cpp EntryContainerStack.cpp OutGoingContainerStack.cpp