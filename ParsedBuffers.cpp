#include <stdexcept>
#include <iostream>

#include "ParsedBuffers.h"

ParsedBuffers::ParsedBuffers(const std::string &filename) : InitialStateReader(filename) {
    parseLines();
}

int ParsedBuffers::getMaxBufferSize(){ return maxBufferSize;}
UntilDue ParsedBuffers::getClearingTime(){ return clearingTime;}
UntilDue ParsedBuffers::getCraneLift(){ return craneLift;}
UntilDue ParsedBuffers::getCraneMove(){ return craneMove;}
UntilDue ParsedBuffers::getCraneLower(){ return craneLower;}
std::vector<Buffer*> ParsedBuffers::getBuffers(){ return buffers;}

void ParsedBuffers::displayBuffers(){
    std::cout<<"maxBufferSize: "<<maxBufferSize<<std::endl;
    std::cout<<"clearingTime: "<<clearingTime.toString()<<std::endl;
    std::cout<<"craneLift: "<<craneLift.toString()<<std::endl;
    std::cout<<"craneMove: "<<craneMove.toString()<<std::endl;
    std::cout<<"craneLower: "<<craneLower.toString()<<std::endl;
}

std::string ParsedBuffers::getDataBetweenTags(
    const std::string line,
    const std::string openingTag,
    const std::string closingTag
){
    int start = line.find(openingTag);
    int end = line.find(closingTag);

    if(start != std::string::npos || end != std::string::npos){
        start += openingTag.length();
        return line.substr(start, end - start);
    }
    throw std::out_of_range("The tag does not exist");
}

UntilDue ParsedBuffers::parseUntilDue(const std::string &input){
    int regexIndex = input.find(":");

    if (regexIndex == std::string::npos || regexIndex == 0 || regexIndex == input.length() - 1)
        throw std::invalid_argument("Input string must be in the format 'min:sec'");

    int min = std::stoi(input.substr(0, regexIndex));
    int sec = std::stoi(input.substr(regexIndex + 1));

    return UntilDue(min, sec);
}

std::vector<Buffer*> ParsedBuffers::parseBuffers(const std::string &line){
    std::vector<std::string> bufferNames = splitStringByRegex(line, '|');

    std::vector<Buffer*> namedBuffers;
    for(int i = 0; i < bufferNames.size(); i++)
        namedBuffers.push_back(new Buffer(maxBufferSize, bufferNames.at(i)));

    return namedBuffers;
}

UntilDueContainer* ParsedBuffers::parseContainer(const std::string &containerDefinition){
    int openParen = containerDefinition.find('(');
    int closeParen = containerDefinition.find(')');

    if (openParen == std::string::npos || closeParen == std::string::npos || closeParen < openParen)
        throw std::invalid_argument("Invalid container definition format");

    std::string id = containerDefinition.substr(0, openParen);
    std::string timeStr = containerDefinition.substr(openParen + 1, closeParen - openParen - 1);
    UntilDue untilDue = parseUntilDue(timeStr);

    return new UntilDueContainer(id, untilDue);
}

void ParsedBuffers::parseContainers(){
    for(int i = 6; i < getLines().size(); i++){
        int count = getRegexCount(getLines().at(i), '|');
        std::vector<std::string> containers = splitStringByRegex(getLines().at(i), '|');
        for(int j = 0; j < count + 1; j++)
            if(!containers.at(j).empty())
                buffers.at(j)->push(*parseContainer(containers.at(j)));
    }
}

void ParsedBuffers::parseLines(){
    maxBufferSize = std::stoi(getDataBetweenTags(getLines().at(0), "<BUFFER SIZE>", "</BUFFER SIZE>"));
    clearingTime = parseUntilDue(getDataBetweenTags(getLines().at(1), "<CLEARING TIME>", "</CLEARING TIME>"));
    craneLift = parseUntilDue(getDataBetweenTags(getLines().at(2), "<CRANE LIFT>", "</CRANE LIFT>"));
    craneMove = parseUntilDue(getDataBetweenTags(getLines().at(3), "<CRANE MOVE>", "</CRANE MOVE>"));
    craneLower = parseUntilDue(getDataBetweenTags(getLines().at(4), "<CRANE LOWER>", "</CRANE LOWER>"));
    buffers = parseBuffers(getLines().at(5));
    parseContainers();
}