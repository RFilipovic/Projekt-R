
#include "RollingMillPrinter.h"

RollingMillPrinter::RollingMillPrinter(MillBuffers &mb, Crane &c1, Crane &c2) : mb(&mb), c1(&c1), c2(&c2){
    NArrivals = getNumberOfStacksInSameCategory('A');
    NBuffers = getNumberOfStacksInSameCategory('B');
    NSortedBuffers = getNumberOfStacksInSameCategory('S');
    NHoldovers = getNumberOfStacksInSameCategory('H');
}

RollingMillPrinter::~RollingMillPrinter() {}

int RollingMillPrinter::getNumberOfStacksInSameCategory(char c){
    int res = 0;
    for(auto& stack : mb->getBuffers()){
        if(stack->getName()[0]==c){
            res++;
        }
    }
    return res;
}

bool RollingMillPrinter::sameCategoryStack(const std::string &stack1,const std::string &stack2){
    if(stack1.empty() || stack2.empty()){
        return false;
    }
    if(stack1[0]==stack2[0]){
        return true;
    }
    return false;
}

int RollingMillPrinter::calculateIndexOfCrane(Crane &crane){
    bool A=0;
    bool B=0;
    bool SB=0;
    bool H=0;
    std::string iznadStoga = crane.getAboveStack(); //pozvati f-ju od kuke koja ce vratiti naziv stoga

    switch (iznadStoga[0])
    {
    case 'A':
        A=1;
        break;
    case 'B':
        B=1;
        break;
    case 'S':
        SB=1;
        break;
    default:
        H=1;
        break;
    }
    int temp = iznadStoga[1]-'0';
    //uvijek trebam sredisnji broj iznad stoga => 1.stog indeks=5
    if(A)
        return (temp+1)*11 + temp - 6;
    if(B)
        return NArrivals*11 + 3 + (temp+1)*11+temp - 6;
    if(SB)
        return NArrivals*11+NArrivals+3 + NBuffers*11+NBuffers+3 + (temp+1)*11+temp - 6;    

    return NArrivals*11+NArrivals+3 + NBuffers*11+NBuffers+3 + (temp+1)*11+temp - 6 + NSortedBuffers*11+NSortedBuffers+3 + (temp+1)*11+temp - 6;
}

//Ne bi trebali sve bit Buffer -> koristiti nove stogove
int RollingMillPrinter::calculateHeight(){
    int maxSize=13;
    int maxOccupancy=0;
    std::vector<Buffer*> buffers = mb->getBuffers();
    for(auto& stack : mb->getBuffers()){
        if(maxOccupancy<stack->stackOccupancy()){
            maxOccupancy = stack->stackOccupancy();
        }
        if (dynamic_cast<Buffer*>(stack)) {
            if(maxSize<stack->getSize()){
                maxSize = stack->getSize();
            }
        }
    }
    return maxSize - maxOccupancy;
}

std::string RollingMillPrinter::centerText(const std::string& text, int width) {
    if (width <= static_cast<int>(text.size())) {
        return text;
    }
    int padding = width - text.size();
    int leftPadding = padding / 2;
    int rightPadding = padding - leftPadding;
    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
}


void RollingMillPrinter::printEverything(){
    const std::string GREEN = "\033[92m";
    const std::string RED = "\033[91m";
    const std::string RESET = "\033[0m";

    std::vector<Buffer*> buffers = mb->getBuffers();
    std::vector<Buffer*> tempStacks;
    for(auto &stack : buffers){
        Buffer* nb = new Buffer(stack->getSize(),stack->getName());
        for(auto &container : stack->getContainers()){
            nb->push(*container);   
        }
        tempStacks.push_back(nb);
    }
    int maxStackHeight = 0;
    for (const auto& stack : buffers) {
        maxStackHeight = std::max(maxStackHeight, stack->stackOccupancy());
    }
    int cranerIndex1 = calculateIndexOfCrane(*c1);
    int cranerIndex2 = calculateIndexOfCrane(*c2);
    int height=calculateHeight();    //->koliko ce redova bit od kuke do dna stogova, potrebno radi zadrzavanja visine "prozora"
    int width=buffers.size()*11 + buffers.size() + 5; //sirina cijelog "prozora", 9=ona 3 puta po 3 razmaka

    //kuka dio PROMIJENI!!!!!!!!!!!!!!!
    int barrierIndex1 = NArrivals*11+NArrivals;
    int barrierIndex2 = NArrivals*11+NArrivals+2 + NBuffers*11+NBuffers+2 + NSortedBuffers*11+NSortedBuffers;
    
    for(int i=0;i<width;i++){
        if(i==0 || i==barrierIndex2)
            std::cout<<RED<<"▀"<<RESET;
        else if(i==width-1 || i==barrierIndex1)
            std::cout<<GREEN<<"▀"<<RESET;
        else if(i==cranerIndex1 || (cranerIndex1==cranerIndex2 && i==cranerIndex1))
            std::cout<<RED<<"|"<<RESET;
        else if(i==cranerIndex2)
            std::cout<<GREEN<<"|"<<RESET;
        else
            std::cout<<"-";
    }
    std::cout<<std::endl;
    
    for(int i=0;i<width;i++){
        if(cranerIndex1==cranerIndex2 && i==cranerIndex1-1){
            std::cout<<"[ ]";
        }
        else if(i==cranerIndex1-1 || i==cranerIndex2-1){
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

    //stogovi dio MALO PROMIJENI
    ContainerStack* prev = NULL;
    for(int currentHeightOfStack = maxStackHeight;currentHeightOfStack>0;currentHeightOfStack--){
        //prolazit po buffers i gledat koliki je size svakog stoga
        // -> ako je jednak chs onda popat element i ispisat ga
        // -> ako nije onda stavit " "
        prev = NULL;
        for(auto& stack : tempStacks){
            if(prev!=NULL && !sameCategoryStack(prev->getName(),stack->getName())){
                std::cout<<"   ";
            }
            else if(prev!=NULL){
                std::cout<<" ";
            }
            prev = stack;
            if(currentHeightOfStack == stack->stackOccupancy()){
                Container* el = stack->pop();
                std::string temp = el->getDetails();
                temp = centerText(temp,11);
                std::cout<<temp;
            }
            else{
                std::string temp = centerText(" ",11);
                std::cout<<temp;
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
        else if(prev!=NULL){
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
        else if(prev!=NULL){
            std::cout<<" ";
        }
        prev = stack;
        std::ostringstream oss;
        oss << stack->getName() << '(' << stack->stackOccupancy() << ')';
        std::string temp = oss.str();
        temp = centerText(temp,11);
        std::cout<<temp;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}

MillBuffers* RollingMillPrinter::getMillBuffers(){
    return mb;
}

Crane* RollingMillPrinter::getC1(){
    return c1;
}
Crane* RollingMillPrinter::getC2(){
    return c2;
}