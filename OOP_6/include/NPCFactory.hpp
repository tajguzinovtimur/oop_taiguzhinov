#ifndef NPCFACTORY_HPP
#define NPCFACTORY_HPP

#include "NPC.hpp"
#include <memory>
#include <string>

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(NPCType type, const std::string& name, int x, int y);
    static std::shared_ptr<NPC> loadFromString(const std::string& data);
    static std::string saveToString(const NPC& npc);
};

#endif