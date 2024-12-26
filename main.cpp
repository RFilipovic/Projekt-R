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
    std::vector<std::string> stackNames = data->getStackNames();
    Crane *crane = new SingleContainerCrane("CRANE", stackNames);
    Printer *p = new Printer(*data, *crane);

    p->printEverything();

    UntilDue lower = data->getCraneLower();
    UntilDue move = data->getCraneMove();
    UntilDue lift = data->getCraneLift();

    while(1){

        int input1, input2;
        std::cout<<"Upisite indeks stoga sa kojeg zelite uzeti kontejner: ";
        std::cin>>input1;
        std::cout<<"Upisite indeks stoga na koji zelite staviti kontejner: ";
        std::cin>>input2;

        crane->setAboveStackIndex(input1);
        UntilDueContainer *container = static_cast<UntilDueContainer*>(data->getBuffers().at(input1)->pop());
        crane->setHookContent(container);
        std::cout<<"Podignut je kontejner "<< container->getDetails()<<std::endl;

        p->printEverything();

        crane->setAboveStackIndex(input2);

        data->getBuffers().at(input2)->push(*container);
        p->printEverything();
    }

    p->printEverything();

    return 0;
}

//g++ main.cpp ParsedBuffers.cpp InitialStateReader.cpp ContainerStack.cpp Buffer.cpp Container.cpp UntilDueContainer.cpp Printer.cpp