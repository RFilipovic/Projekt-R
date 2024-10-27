#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <sstream>

#include "containers.h"

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

Container::Container(const std::string &id) : id(id) {}
Container::~Container() {}

UntilDueContainer::UntilDueContainer(const std::string &id, const UntilDue &untilDue)
    : Container(id), untilDue(untilDue) {}

void UntilDueContainer::displayDetails() const  {
    std::cout << id << " " << untilDue.toString() << std::endl;
}

UntilDue UntilDueContainer::getUntilDue() const { return untilDue; }
void UntilDueContainer::setUntilDue(const UntilDue &newUntilDue) { untilDue = newUntilDue; }

PriorityContainer::PriorityContainer(const std::string &id, int priority, const std::string &destination)
        : Container(id), priority(priority), destination(destination) {}

void PriorityContainer::displayDetails() const {
        std::cout << id << " " << priority << " " << destination << std::endl;
}