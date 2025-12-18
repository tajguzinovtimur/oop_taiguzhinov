#include "NPCFactory.hpp"
#include <sstream>
#include <iostream>

std::shared_ptr<NPC> NPCFactory::createNPC(NPCType type, const std::string& name, int x, int y) {
    switch (type) {
        case NPCType::ORC:
            return std::make_shared<Orc>(name, x, y);
        case NPCType::SQUIRREL:
            return std::make_shared<Squirrel>(name, x, y);
        case NPCType::DRUID:
            return std::make_shared<Druid>(name, x, y);
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}

std::shared_ptr<NPC> NPCFactory::loadFromString(const std::string& data) {
    std::istringstream iss(data);
    std::string typeStr, name;
    int x, y;
    
    if (!(iss >> typeStr >> name >> x >> y)) {
        throw std::runtime_error("Invalid NPC data format");
    }
    
    NPCType type;
    if (typeStr == "ORC") type = NPCType::ORC;
    else if (typeStr == "SQUIRREL") type = NPCType::SQUIRREL;
    else if (typeStr == "DRUID") type = NPCType::DRUID;
    else throw std::runtime_error("Unknown NPC type: " + typeStr);
    
    return createNPC(type, name, x, y);
}

std::string NPCFactory::saveToString(const NPC& npc) {
    std::ostringstream oss;
    oss << npc.getTypeName() << " " << npc.getName() << " " << npc.getX() << " " << npc.getY();
    return oss.str();
}