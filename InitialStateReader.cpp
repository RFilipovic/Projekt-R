#include <fstream>

#include "InitialStateReader.h"

InitialStateReader::InitialStateReader(const std::string &filename) : filename(filename) {
    lines = readFile(filename);
}

std::vector<std::string> InitialStateReader::getLines(){
    return lines;
}

std::vector<std::string> InitialStateReader::readFile(const std::string &filename){
    std::ifstream file(filename);
    if(!file.is_open()) throw std::runtime_error("Could not open file: " + filename);

    std::string line;
    std::vector<std::string> lines;
    while(std::getline(file, line)){
        lines.push_back(line);
    }
    
    return lines;
}