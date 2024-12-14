#include <iostream>
#include <vector>
#include <iomanip>

#include "ParsedBuffers.h"
#include "Buffer.h"
#include "ContainerStack.h"
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

bool sameCategoryStack(const std::string &stack1,const std::string &stack2){
    if(stack1.empty() || stack2.empty()){
        return false;
    }
    if(stack1[0]==stack2[0]){
        return true;
    }
    return false;
}

void printEverything(ParsedBuffers pb){
    std::vector<Buffer*> buffers = pb.getBuffers();
    int maxStackHeight = 0;
    for (const auto& stack : buffers) {
        maxStackHeight = std::max(maxStackHeight, stack->getSize());
    }
    int HookIndex = 0 + 5;  //pozvati f-ju kuke koja vrati broj stoga iznad kojeg se nalazi
    int height=4; //koliko ce redova bit od kuke do dna stogova, bzvz 10 zasad
    int width=buffers.size()*10 + buffers.size(); //sirina cijelog "prozora" koji prikazuje sve

    //kuka dio
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

    //stogovi dio
    ContainerStack* prev = NULL;
   for(int currentHeightOfStack = maxStackHeight;currentHeightOfStack>0;currentHeightOfStack--){
        //prolazit po buffers i gledat koliki je size svakog stoga
        // -> ako je jednak chs onda popat element i ispisat ga
        // -> ako nije onda stavit " "
        prev = NULL;
        for(auto& stack : buffers){
            if(prev!=NULL && !sameCategoryStack(prev->getName(),stack->getName())){
                std::cout<<"   ";
            }
            else{
                std::cout<<" ";
            }
            prev = stack;
            if(currentHeightOfStack == stack->getSize()){
                Container* el = stack->pop();
                el->displayDetails();
            }
            else{
                std::cout<<std::setw(11)<<"x";
            }
        }
        std::cout<<std::endl;
   }

   //ispis dna i naziva pojedinog stoga
    prev = NULL;
    for(auto& stack : buffers){
        if(prev!=NULL && !sameCategoryStack(prev->getName(),stack->getName())){
            std::cout<<"   ";
        }
        else{
            std::cout<<" ";
        }
        prev = stack;
        for(int i=0;i<11;i++){
            std::cout<<"-";
        }
    }
    std::cout<<std::endl;

    prev = NULL;
    for(auto& stack : buffers){
    if(prev!=NULL && !sameCategoryStack(prev->getName(),stack->getName())){
        std::cout<<"   ";
    }
    else{
        std::cout<<" ";
    }
        std::cout<<std::setw(11)<<stack->getName();
    }
    std::cout<<std::endl;
}


//potrebna f-ja za smanjivanje vremena na svakom kontejneru

//g++ main.cpp ParsedBuffers.cpp InitialStateReader.cpp ContainerStack.cpp Buffer.cpp Container.cpp UntilDueContainer.cpp