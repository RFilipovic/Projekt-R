#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "SingleContainerCrane.h"
#include "Printer.h"
#include "ParsedBuffers.h"
#include <fstream> // Za rad s datotekama

class HotStorageSimulator
{
public:
    HotStorageSimulator(Printer &p);
    void simulate();

private:
    Printer *printer;
    void runEntryStack();
    void runCrane();
    void runOutgoingStack();

    // Funkcija za učitavanje naredbi iz datoteke
    bool getNextCommandFromFile(std::ifstream &file, int &input1, int &input2);
};

#endif // SIMULATOR_H
