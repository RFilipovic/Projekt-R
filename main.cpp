#include <iostream>
#include <vector>
#include <iomanip>

#include "ParsedBuffers.h"
#include "Buffer.h"
#include "Container.h"

void printEverything(ParsedBuffers pb);

int main(){

    ParsedBuffers *data = new ParsedBuffers("ulaz.txt");

/*     for(auto buffer : data->getBuffers()){
        std::cout<<buffer->getName()<<std::endl;
        //buffer->printStack();
        std::cout<<std::endl;
    } */
    printEverything(*data);

    return 0;
}



void printEverything(ParsedBuffers pb){
    std::vector<Buffer*> temp = pb.getBuffers();
    int maxStackHeight = 0;
    for (const auto& stack : temp) {
        maxStackHeight = std::max(maxStackHeight, stack->getSize());
    }
    int HookIndex = 0 + 5;  //pozvati f-ju kuke koja vrati broj stoga iznad kojeg se nalazi
    int height=4; //koliko ce redova bit od kuke do dna stogova, bzvz 10 zasad
    int width=temp.size()*10 + temp.size(); //sirina cijelog "prozora" koji prikazuje sve

    for(int i=0;i<width;i++){
        if(i==HookIndex+1){
            std::cout<<"|";
        }
        else{
            std::cout<<"-";
        }
    }
    std::cout<<std::endl;
    for(int i=0;i<width;i++){
        if(i==HookIndex){
            std::cout<<"[ ]";
        }
        else{
            std::cout<<" ";
        }
    }
    std::cout<<std::endl; 
    for(int i=0;i<height;i++){
        std::cout<<std::endl;
    }

   for(int currentHeightOfStack = maxStackHeight;currentHeightOfStack>0;currentHeightOfStack--){
        //prolazit po temp i gledat koliki je size svakog stoga
        // -> ako je jednak chs onda popat element i ispisat ga
        // -> ako nije onda stavit " "
        for(auto& stack : temp){
            if(currentHeightOfStack == stack->getSize()){
                Container* el = stack->pop();
                el->displayDetails();
                //std::cout<<" ";
            }
            else{
                std::cout<<std::setw(11)<<"x";
            }
        }
        std::cout<<std::endl;
   }
   for(int i=0;i<width;i++){
    if(i%11==0){
        std::cout<<" ";
    }
    else{
        std::cout<<"-";
    }
   }
   std::cout<<std::endl;

   for(auto& stack : temp){
        std::cout<<std::setw(11)<<stack->getName();
    }
    std::cout<<std::endl;
}


//potrebna f-ja za smanjivanje vremena na svakom kontejneru

//g++ main.cpp ParsedBuffers.cpp InitialStateReader.cpp ContainerStack.cpp Buffer.cpp Container.cpp UntilDueContainer.cpp