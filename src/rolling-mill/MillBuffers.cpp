#include <stdexcept>
#include <iostream>

#include "MillBuffers.h"
#include "EntryContainerStack.h"
#include "OutGoingContainerStack.h"
#include "PriorityContainer.h"

MillBuffers::MillBuffers(const std::string &filename) : InitialStateReader(filename)
{
    parseLines();
}

int MillBuffers::getBufferSize() { return bufferSize; }
UntilDue MillBuffers::getClearingTime() { return clearingTime; }
UntilDue MillBuffers::getCraneLiftC1() { return craneLift; }
UntilDue MillBuffers::getCraneMoveC1() { return craneMove; }
UntilDue MillBuffers::getCraneLowerC1() { return craneLower; }
UntilDue MillBuffers::getCraneLiftC2() { return craneLiftC2; }
UntilDue MillBuffers::getCraneMoveC2() { return craneMoveC2; }
UntilDue MillBuffers::getCraneLowerC2() { return craneLowerC2; }
std::vector<Buffer *> MillBuffers::getBuffers() { return buffers; }

void MillBuffers::displayBuffers()
{
    std::cout << "maxBufferSize: " << bufferSize << std::endl;
    std::cout << "clearingTime: " << clearingTime.toString() << std::endl;
    std::cout << "craneLift: " << craneLift.toString() << std::endl;
    std::cout << "craneMove: " << craneMove.toString() << std::endl;
    std::cout << "craneLower: " << craneLower.toString() << std::endl;
}

std::string MillBuffers::getDataBetweenTags(
    const std::string line,
    const std::string openingTag,
    const std::string closingTag)
{
    int start = line.find(openingTag);
    int end = line.find(closingTag);

    if (start != std::string::npos || end != std::string::npos)
    {
        start += openingTag.length();
        return line.substr(start, end - start);
    }
    throw std::out_of_range("The tag does not exist");
}

UntilDue MillBuffers::parseUntilDue(const std::string &input)
{
    int regexIndex = input.find(":");

    if (regexIndex == std::string::npos || regexIndex == 0 || regexIndex == input.length() - 1)
        throw std::invalid_argument("Input string must be in the format 'min:sec'");

    int min = std::stoi(input.substr(0, regexIndex));
    int sec = std::stoi(input.substr(regexIndex + 1));

    return UntilDue(min, sec);
}

std::vector<Buffer *> MillBuffers::parseBuffers(const std::string &line)
{
    std::vector<std::string> bufferNames = splitStringByRegex(line, '|');
    stackNames = bufferNames;

    std::vector<Buffer *> namedBuffers;
    for (int i = 0; i < bufferNames.size(); ++i)
    {
        if (i < 3)
        { // First 3 are incoming stacks
            namedBuffers.push_back(new EntryContainerStack());
        }
        else if (i < 6)
        { // Next 3 are unsorted buffers
            namedBuffers.push_back(new Buffer(bufferSize, bufferNames.at(i)));
        }
        else if (i < 9)
        { // Next 3 are sorted buffers
            namedBuffers.push_back(new Buffer(bufferSize, bufferNames.at(i)));
        }
        else if (i == 9)
        { // Blue outgoing stack
            blueOutgoingStack = new OutGoingContainerStack();
            namedBuffers.push_back(blueOutgoingStack);
        }
        else if (i == 10)
        { // Purple outgoing stack
            purpleOutgoingStack = new OutGoingContainerStack();
            namedBuffers.push_back(purpleOutgoingStack);
        }
    }

    return namedBuffers;
}

PriorityContainer *MillBuffers::parseContainer(const std::string &containerDefinition)
{
    int firstSlash = containerDefinition.find('/');
    int secondSlash = containerDefinition.find('/', firstSlash + 1);

    if (firstSlash == std::string::npos || secondSlash == std::string::npos)
        throw std::invalid_argument("Invalid container definition format. Expected format: id/priority/destination");

    std::string id = containerDefinition.substr(0, firstSlash);
    int priority = std::stoi(containerDefinition.substr(firstSlash + 1, secondSlash - firstSlash - 1));
    std::string destination = containerDefinition.substr(secondSlash + 1);

    return new PriorityContainer(id, priority, destination);
}

void MillBuffers::parseContainers()
{
    for (int i = 9; i < getLines().size(); i++)
    {
        int count = getRegexCount(getLines().at(i), '|');
        std::vector<std::string> containers = splitStringByRegex(getLines().at(i), '|');
        for (int j = 3; j < count + 1; j++)
            if (!containers.at(j).empty())
                buffers.at(j)->push(*parseContainer(containers.at(j)));
    }
}

void MillBuffers::parseLines()
{

    std::vector<std::string> lines = getLines();

    bufferSize = std::stoi(getDataBetweenTags(lines.at(0), "<MAX VISINA BUFFERA>", "</MAX VISINA BUFFERA>"));

    clearingTime = parseUntilDue(getDataBetweenTags(lines.at(1), "<clearing time>", "</clearing time>"));

    craneLift = parseUntilDue(getDataBetweenTags(lines.at(2), "<trajanje podizanja C1>", "</trajanje podizanja>"));
    craneMove = parseUntilDue(getDataBetweenTags(lines.at(3), "<trajanje premještanja C1>", "</trajanje premještanja>"));
    craneLower = parseUntilDue(getDataBetweenTags(lines.at(4), "<trajanje spuštanja C1>", "</trajanje spuštanja>"));

    craneLiftC2 = parseUntilDue(getDataBetweenTags(lines.at(5), "<trajanje podizanja C2>", "</trajanje podizanja>"));
    craneMoveC2 = parseUntilDue(getDataBetweenTags(lines.at(6), "<trajanje premještanja C2>", "</trajanje premještanja>"));
    craneLowerC2 = parseUntilDue(getDataBetweenTags(lines.at(7), "<trajanje spuštanja C2>", "</trajanje spuštanja>"));

    buffers = parseBuffers(getLines().at(8));

    parseContainers();
}

std::vector<std::string> MillBuffers::getStackNames()
{
    return stackNames;
}

void MillBuffers::refreshTime(UntilDue time)
{
    int refreshSeconds = time.getSeconds();
    int refreshMinutes = time.getMinutes();

    for (Buffer *buffer : buffers)
    {
        for (Container *container : buffer->getContainers())
        {
            UntilDueContainer *udc = dynamic_cast<UntilDueContainer *>(container);

            int min = udc->getUntilDue().getMinutes() - refreshMinutes, sec = udc->getUntilDue().getSeconds() - refreshSeconds;

            if (min > 0 && sec < 0 || min <= 0 && sec <= -60)
            {
                min -= 1;
                sec += 60;
            }

            UntilDue time(min, sec);
            udc->setUntilDue(time);
        }
    }
}