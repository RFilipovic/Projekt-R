#include <iostream>

#include "ParsedBuffers.h"

int main(){

    ParsedBuffers *data = new ParsedBuffers("ulaz.txt");

    for(auto buffer : data->getBuffers()){
        std::cout<<buffer->getName()<<std::endl;
        buffer->printStack();
        std::cout<<std::endl;
    }

    return 0;
}