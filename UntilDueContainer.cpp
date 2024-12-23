#include <iostream>
#include <string>
#include <iomanip>

#include "UntilDueContainer.h"

UntilDue::UntilDue() {}

UntilDue::UntilDue(int minutes, int seconds) : minutes(minutes), seconds(seconds) {
    if (minutes < 0 || seconds < 0 || seconds >= 60) {
        throw std::invalid_argument("Invalid time format");
    }
}

std::string UntilDue::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}

UntilDueContainer::UntilDueContainer(const std::string &id, const UntilDue &untilDue)
    : Container(id), untilDue(untilDue) {}

void UntilDueContainer::displayDetails() const  {
    std::cout << id << " " << untilDue.toString() << std::endl;
}

UntilDue UntilDueContainer::getUntilDue() const { return untilDue; }

void UntilDueContainer::setUntilDue(const UntilDue &newUntilDue) { untilDue = newUntilDue; }