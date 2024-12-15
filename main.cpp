#include <iostream>
#include <vector>
#include <iomanip>

#include "ParsedBuffers.h"
#include "Buffer.h"
#include "ContainerStack.h"
#include "Container.h"
#include "Printer.h"

void printEverything(ParsedBuffers pb);

int main(){

    ParsedBuffers *data = new ParsedBuffers("ulaz.txt");
    Printer *p = new Printer(*data);

    p->printEverything();

    return 0;
}

//potrebna f-ja za smanjivanje vremena na svakom kontejneru

//g++ main.cpp ParsedBuffers.cpp InitialStateReader.cpp ContainerStack.cpp Buffer.cpp Container.cpp UntilDueContainer.cpp