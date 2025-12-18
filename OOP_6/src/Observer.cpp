#include "Observer.hpp"
#include <iostream>
#include <fstream>

// ConsoleObserver
void ConsoleObserver::update(const std::string& message) {
    std::cout << "[CONSOLE LOG] " << message << std::endl;
}

// FileObserver
FileObserver::FileObserver(const std::string& filename) : filename(filename) {}

void FileObserver::update(const std::string& message) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << "[FILE LOG] " << message << std::endl;
        file.close();
    }
}

// Subject
void Subject::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Subject::notify(const std::string& message) {
    for (auto& observer : observers) {
        observer->update(message);
    }
}