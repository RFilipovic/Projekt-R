#ifndef PARSEDBUFFERS_H
#define PARSEDBUFFERS_H

#include "InitialStateReader.h"
#include "containers.h"

class ParsedBuffers : public InitialStateReader {
    public:
        ParsedBuffers(const std::string &filename);
        int getMaxBufferSize();
        UntilDue getClearingTime();
        UntilDue getCraneLift();
        UntilDue getCraneMove();
        UntilDue getCraneLower();
        void displayBuffers();
    private:
        int maxBufferSize;
        UntilDue clearingTime;
        UntilDue craneLift;
        UntilDue craneMove;
        UntilDue craneLower;
        void parseLines();
        std::string getDataBetweenTags(
            const std::string line,
            const std::string openingTag,
            const std::string closingTag
        );
        UntilDue parseUntilDue(const std::string &input);
};

#endif // PARSEDBUFFERS_H