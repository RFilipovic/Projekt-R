#include <unistd.h>
#include <thread>

#include "HotStorageSimulator.h"
#include "EntryContainerStack.h"

HotStorageSimulator::HotStorageSimulator(Printer &p){
        *this->printer = p;
}

//dretvene funkcije
//pokrece dolazni stog paralelno
void HotStorageSimulator::runEntryStack(){

    auto data = printer->getParsedBuffers();
    EntryContainerStack *entryStack = dynamic_cast<EntryContainerStack*>(data->getBuffers().at(0));

    while (1)
    {
        entryStack->startAutoAddContainers(1, 4);
    }
}

//pokrece kuku paralelno
void HotStorageSimulator::runCrane(){
    printer->printEverything();

    auto data = printer->getParsedBuffers();
    SingleContainerCrane *crane = dynamic_cast<SingleContainerCrane*>(printer->getCrane());
    EntryContainerStack *entryStack = dynamic_cast<EntryContainerStack*>(data->getBuffers().at(0));

    UntilDue lower = data->getCraneLower();
    UntilDue move = data->getCraneMove();
    UntilDue lift = data->getCraneLift();

    while(1){

        int input1, input2;
        std::cout<<"Upisite indeks stoga sa kojeg zelite uzeti kontejner: ";
        std::cin>>input1;
        std::cout<<"Upisite indeks stoga na koji zelite staviti kontejner: ";
        std::cin>>input2;

        if(input1 == input2){
            std::cout<<"Ne mozete premjestiti kontejner na isti stog!"<<std::endl;
            continue;
        }else if(input2 == 0){
            std::cout<<"Ne mozete stavljati kontejnere na dolazni stog!"<<std::endl;
            continue;
        }

        if(input1 != 0) entryStack->continueTime();
        
        if(input1 != crane->getAboveStackIndex()){
            data->refreshTime(move);
            sleep(move.getMinutes() * 60 + move.getSeconds());
            crane->setAboveStackIndex(input1);
            std::cout<<"Kuka je pomaknuta iznad stoga "<< crane->getAboveStack() <<std::endl;
            printer->printEverything();
        }

        data->refreshTime(lower);
        std::cout<<"Kuka se spusta."<<std::endl;
        sleep(lower.getMinutes() * 60 + lower.getSeconds());
        std::cout<<"Kuka se spustila, skupila kontejner i pocela se dizat."<<std::endl;

        UntilDueContainer *container = static_cast<UntilDueContainer*>(data->getBuffers().at(input1)->pop());
        crane->setHookContent(container);

        entryStack->continueTime();

        data->refreshTime(lift);
        sleep(lift.getMinutes() * 60 + lift.getSeconds());
        crane->refreshTime(lift);

        std::cout<<"Podignut je kontejner "<< container->getDetails()<<std::endl;

        printer->printEverything();

        crane->setAboveStackIndex(input2);

        data->refreshTime(move);
        crane->refreshTime(move);
        sleep(move.getMinutes() * 60 + move.getSeconds());
        std::cout<<"Kuka je pomaknuta iznad stoga "<< crane->getAboveStack() <<std::endl;
        printer->printEverything();

        data->refreshTime(lower);
        crane->refreshTime(lower);
        std::cout<<"Kuka se spusta."<<std::endl;
        sleep(lower.getMinutes() * 60 + lower.getSeconds());

        data->getBuffers().at(input2)->push(*container);
        std::cout<<"Kuka je ostavila kontejner na stog i pocela se dizat."<<std::endl;
        printer->printEverything();

        data->refreshTime(lift);
        sleep(lift.getMinutes() * 60 + lift.getSeconds());
        std::cout<<"Kuka spremna za iducu naredbu —>"<<std::endl;
        printer->printEverything();

        entryStack->pauseTime();
    }
}

//pokrece odlazni stog paralelno
void HotStorageSimulator::runOutgoingStack(){

}

void HotStorageSimulator::simulate(){
    
    std::thread entryStack([this]() { this->runEntryStack(); });
    std::thread crane([this]() { this->runCrane(); });

    entryStack.join();
    crane.join();
    
}