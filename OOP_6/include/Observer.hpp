#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <string>
#include <memory>
#include <vector>

class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override;
};

class FileObserver : public Observer {
private:
    std::string filename;
public:
    FileObserver(const std::string& filename);
    void update(const std::string& message) override;
};

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void addObserver(std::shared_ptr<Observer> observer);
    void notify(const std::string& message);
};

#endif