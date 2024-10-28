#ifndef INITIALSTATEREADER_H
#define INITIALSTATEREADER_H

#include <string>
#include <vector>

class InitialStateReader {
    public:
        InitialStateReader(const std::string &filename);
        std::vector<std::string> getLines();
    private:
        std::string filename;
        std::vector<std::string> lines;
        std::vector<std::string> readFile(const std::string &filename);
};

#endif // INITIALSTATEREADER_H