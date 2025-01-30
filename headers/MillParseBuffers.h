#ifndef MILLPARSEBUFFERS_H
#define MILLPARSEBUFFERS_H

#include <vector>
#include <string.h>
#include "UntilDueContainer.h"
#include "InitialStateReader.h"
#include "PriorityContainer.h"
#include "PriorityOutGoingContainerStack.h"
#include "SortedPriorityBuffer.h"
#include "EntryContainerMill.h"

class MillParseBuffers : public InitialStateReader {
    public:
        MillParseBuffers(const std::string &filename);
        int getBufferSize();
        UntilDue getClearingTime();
        UntilDue getCraneLiftC1();
        UntilDue getCraneMoveC1();
        UntilDue getCraneLowerC1();
        UntilDue getCraneLiftC2();
        UntilDue getCraneMoveC2();
        UntilDue getCraneLowerC2();
        std::vector<SortedPriorityBuffer*> getBuffers();
        void displayBuffers();
        std::vector<std::string> getStackNames();
        void refreshTime(UntilDue time);

    private:
        int bufferSize;
        UntilDue clearingTime;
        UntilDue craneLift;
        UntilDue craneMove;
        UntilDue craneLower;
        std::vector<SortedPriorityBuffer*> buffers;
        std::vector<std::string> stackNames;
        PriorityOutGoingContainerStack* blueOutgoingStack;
        PriorityOutGoingContainerStack* purpleOutgoingStack;
        UntilDue craneLiftC2;
        UntilDue craneMoveC2;
        UntilDue craneLowerC2;

        std::string getDataBetweenTags(
            const std::string line,
            const std::string openingTag,
            const std::string closingTag
        );
        UntilDue parseUntilDue(const std::string &input);
        std::vector<SortedPriorityBuffer*> parseBuffers(const std::string &line);
        PriorityContainer* parseContainer(const std::string &containerDefinition);
        void parseContainers();
        void parseLines();
};

#endif // MILLBUFFERS_H