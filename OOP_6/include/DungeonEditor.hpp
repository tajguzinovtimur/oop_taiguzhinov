#ifndef DUNGEONEDITOR_HPP
#define DUNGEONEDITOR_HPP

#include "NPC.hpp"
#include "Observer.hpp"
#include <vector>
#include <memory>
#include <string>

class DungeonEditor {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    Subject battleLogger;

public:
    void addNPC(NPCType type, const std::string& name, int x, int y);
    void printAll() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void battle(int range);
    void addObserver(std::shared_ptr<Observer> observer);
};

#endif