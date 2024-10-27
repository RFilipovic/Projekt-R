#ifndef CONTAINERS_H
#define CONTAINERS_H

class UntilDue {
    public:
        UntilDue(int minutes, int seconds);
        std::string toString() const;
    private:
        int minutes;
        int seconds;
};

class Container {
    public:
        Container(const std::string &id);
        virtual ~Container();
        virtual void displayDetails() const = 0;
    protected:
        std::string id;
};

class UntilDueContainer : public Container{
    public:
        UntilDueContainer(const std::string &id, const UntilDue &untilDue);
        void displayDetails() const;
        UntilDue getUntilDue() const;
        void setUntilDue(const UntilDue &newUntilDue);
    private:
        UntilDue untilDue;
};

#endif // CONTAINERS_H