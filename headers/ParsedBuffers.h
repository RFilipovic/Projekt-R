#ifndef PARSEDBUFFERS_H
#define PARSEDBUFFERS_H

#include <vector>
#include "UntilDueContainer.h"
#include "InitialStateReader.h"
#include "Buffer.h"

class ParsedBuffers : public InitialStateReader {
    public:
        ParsedBuffers(const std::string &filename);
        int getBufferSize();
        UntilDue getClearingTime();
        UntilDue getCraneLiftC1();
        UntilDue getCraneMoveC1();
        UntilDue getCraneLowerC1();
        UntilDue getCraneLiftC2();
        UntilDue getCraneMoveC2();
        UntilDue getCraneLowerC2();
        std::vector<Buffer*> getBuffers();
        void displayBuffers();
        std::vector<std::string> getStackNames();
        void refreshTime(UntilDue time);

    private:
        int bufferSize;
        UntilDue clearingTime;
        UntilDue craneLift;
        UntilDue craneMove;
        UntilDue craneLower;
        std::vector<Buffer*> buffers;
        std::vector<std::string> stackNames;
        OutGoingContainerStack* blueOutgoingStack;
        OutGoingContainerStack* purpleOutgoingStack;
        UntilDue craneLiftC2;
        UntilDue craneMoveC2;
        UntilDue craneLowerC2;

        std::string getDataBetweenTags(
            const std::string line,
            const std::string openingTag,
            const std::string closingTag
        );
        UntilDue parseUntilDue(const std::string &input);
        std::vector<Buffer*> parseBuffers(const std::string &line);
        PriorityContainer* parseContainer(const std::string &containerDefinition);
        void parseContainers();
        void parseLines();
};

#endif // PARSEDBUFFERS_H