#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <sstream>

class UntilDue
{
public:
    UntilDue(int minutes, int seconds) : minutes(minutes), seconds(seconds)
    {
        if (minutes < 0 || seconds < 0 || seconds >= 60)
        {
            throw std::invalid_argument("Invalid time format");
        }
    }

    std::string toString() const
    {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;
        return oss.str();
    }

private:
    int minutes;
    int seconds;
};

class Container
{
public:
    Container(const std::string &id) : id(id) {}
    virtual ~Container() {}
    virtual void displayDetails() const = 0;

protected:
    std::string id;
};

class UntilDueContainer : public Container
{
public:
    UntilDueContainer(const std::string &id, const UntilDue &untilDue)
        : Container(id), untilDue(untilDue) {}

    void displayDetails() const override
    {
        std::cout << id << " " << untilDue.toString() << std::endl;
    }

   
    UntilDue getUntilDue() const { return untilDue; }

  
    void setUntilDue(const UntilDue &newUntilDue) { untilDue = newUntilDue; }

private:
    UntilDue untilDue;
};

class PriorityContainer : public Container
{
public:
    PriorityContainer(const std::string &id, int priority, const std::string &destination)
        : Container(id), priority(priority), destination(destination) {}

    void displayDetails() const override
    {
        std::cout << id << " " << priority << " " << destination << std::endl;
    }

private:
    int priority;
    std::string destination;
};
