#ifndef UNTILDUECONTAINER_H
#define UNTILDUECONTAINER_H

#include "Container.h"

class UntilDue {
    public:
        UntilDue();
        UntilDue(int minutes, int seconds);
        std::string toString() const;
    private:
        int minutes;
        int seconds;
};

class UntilDueContainer : public Container {
    public:
        UntilDueContainer(const std::string &id, const UntilDue &untilDue);
        void displayDetails() const;
        std::string getDetails() const;
        UntilDue getUntilDue() const;
        void setUntilDue(const UntilDue &newUntilDue);
    private:
        UntilDue untilDue;
};

#endif //UNTILDUECONTAINER_H