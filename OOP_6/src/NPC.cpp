#include "NPC.hpp"
#include <iostream>
#include <cmath>

// Базовый класс NPC
NPC::NPC(NPCType type, const std::string& name, int x, int y) 
    : type(type), name(name), x(x), y(y) {}

NPCType NPC::getType() const { return type; }
std::string NPC::getName() const { return name; }
int NPC::getX() const { return x; }
int NPC::getY() const { return y; }

void NPC::print() const {
    std::cout << getTypeName() << " '" << name << "' at (" << x << ", " << y << ")" << std::endl;
}

bool NPC::isWithinRange(const NPC& other, int range) const {
    int dx = x - other.x;
    int dy = y - other.y;
    return (dx * dx + dy * dy) <= (range * range);
}

// Конкретные классы NPC
Orc::Orc(const std::string& name, int x, int y) 
    : NPC(NPCType::ORC, name, x, y) {}

std::string Orc::getTypeName() const { return "Orc"; }

Squirrel::Squirrel(const std::string& name, int x, int y) 
    : NPC(NPCType::SQUIRREL, name, x, y) {}

std::string Squirrel::getTypeName() const { return "Squirrel"; }

Druid::Druid(const std::string& name, int x, int y) 
    : NPC(NPCType::DRUID, name, x, y) {}

std::string Druid::getTypeName() const { return "Druid"; }