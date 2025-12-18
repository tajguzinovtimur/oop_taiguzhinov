#include "BattleVisitor.hpp"
#include "NPC.hpp"
#include <iostream>

bool BattleRuleVisitor::visit(Orc& orc, NPC& other) {
    // Орк убивает друидов
    if (other.getType() == NPCType::DRUID) {
        std::cout << orc.getName() << " (Orc) kills " << other.getName() << " (Druid)" << std::endl;
        return true;
    }
    return false;
}

bool BattleRuleVisitor::visit(Squirrel& squirrel, NPC& other) {
    // Белки за мир - никого не убивают
    std::cout << squirrel.getName() << " (Squirrel) is peaceful, does not fight" << std::endl;
    return false;
}

bool BattleRuleVisitor::visit(Druid& druid, NPC& other) {
    // Друид убивает белок
    if (other.getType() == NPCType::SQUIRREL) {
        std::cout << druid.getName() << " (Druid) kills " << other.getName() << " (Squirrel)" << std::endl;
        return true;
    }
    return false;
}

// Реализация accept методов для NPC (их можно разместить здесь или в NPC.cpp)

bool Orc::accept(BattleVisitor& visitor, NPC& other) {
    return visitor.visit(*this, other);
}

bool Squirrel::accept(BattleVisitor& visitor, NPC& other) {
    return visitor.visit(*this, other);
}

bool Druid::accept(BattleVisitor& visitor, NPC& other) {
    return visitor.visit(*this, other);
}