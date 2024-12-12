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
        UntilDue getCraneLift();
        UntilDue getCraneMove();
        UntilDue getCraneLower();
        std::vector<Buffer*> getBuffers();
        void displayBuffers();
    private:
        int bufferSize;
        UntilDue clearingTime;
        UntilDue craneLift;
        UntilDue craneMove;
        UntilDue craneLower;
        std::vector<Buffer*> buffers;

        std::string getDataBetweenTags(
            const std::string line,
            const std::string openingTag,
            const std::string closingTag
        );
        UntilDue parseUntilDue(const std::string &input);
        std::vector<Buffer*> parseBuffers(const std::string &line);
        UntilDueContainer* parseContainer(const std::string &containerDefinition);
        void parseContainers();
        void parseLines();
};

#endif // PARSEDBUFFERS_H