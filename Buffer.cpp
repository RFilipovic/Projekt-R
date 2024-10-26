#include<iostream>

#include "ContainerStack.h"
#include "Buffer.h"

Buffer::Buffer(int size) : size(size){}

bool Buffer::isFull(){
    if(containers.size()>=size){
        return true;
    }
    return false;
}
        
bool Buffer::push(Container* container){
    if(containers.size()>=size){
        return false;
    }
    else{
        containers.push_back(container);
        return true;
    }
}