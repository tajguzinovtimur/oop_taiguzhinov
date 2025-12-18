#include "DungeonEditor.hpp"
#include "NPCFactory.hpp"
#include "BattleVisitor.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

void DungeonEditor::addNPC(NPCType type, const std::string& name, int x, int y) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::out_of_range("Coordinates must be in range [0, 500]");
    }
    npcs.push_back(NPCFactory::createNPC(type, name, x, y));
}

void DungeonEditor::printAll() const {
    if (npcs.empty()) {
        std::cout << "No NPCs in the dungeon." << std::endl;
        return;
    }
    
    for (const auto& npc : npcs) {
        npc->print();
    }
}

void DungeonEditor::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    for (const auto& npc : npcs) {
        file << NPCFactory::saveToString(*npc) << std::endl;
    }
    file.close();
}

void DungeonEditor::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    npcs.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                npcs.push_back(NPCFactory::loadFromString(line));
            } catch (const std::exception& e) {
                std::cerr << "Error loading NPC: " << e.what() << std::endl;
            }
        }
    }
    file.close();
}

void DungeonEditor::battle(int range) {
    BattleRuleVisitor visitor;
    std::vector<std::shared_ptr<NPC>> survivors;
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        bool killed = false;
        
        for (size_t j = 0; j < npcs.size(); ++j) {
            if (i == j) continue;
            
            if (npcs[i]->isWithinRange(*npcs[j], range)) {
                // NPC i атакует NPC j
                if (npcs[i]->accept(visitor, *npcs[j])) {
                    std::string message = npcs[i]->getName() + " killed " + npcs[j]->getName();
                    battleLogger.notify(message);
                    // NPC j убит, помечаем для удаления
                    killed = true;
                    break;
                }
            }
        }
        
        if (!killed) {
            survivors.push_back(npcs[i]);
        }
    }
    
    npcs = survivors;
}

void DungeonEditor::addObserver(std::shared_ptr<Observer> observer) {
    battleLogger.addObserver(observer);
}