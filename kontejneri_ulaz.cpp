#include <iostream>
#include <string>
#include <iomanip>

class TimeDate
{
public:
    TimeDate(int minutes, int seconds) : minutes(minutes), seconds(seconds)
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

class HotStorage : public Container
{
public:
    HotStorage(const std::string &id, const TimeDate &untilDue)
        : Container(id), untilDue(untilDue) {}

    void displayDetails() const override
    {
        std::cout << id << " " << untilDue.toString() << " " << std::endl;
    }

private:
    TimeDate untilDue;
};

class RollingMill : public Container
{
public:
    RollingMill(const std::string &id, int deliveryNumber, const std::string &destination)
        : Container(id), priority(priority), destination(destination) {}

    void displayDetails() const override
    {
        std::cout << id << " " << priority
                  << " " << destination << std::endl;
    }

private:
    int priority;
    std::string destination;
};
