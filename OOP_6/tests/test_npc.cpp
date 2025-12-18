// tests/test_npc.cpp
#include <gtest/gtest.h>
#include "NPC.hpp"
#include "NPCFactory.hpp"
#include "BattleVisitor.hpp"

TEST(NPCTest, OrcKillsDruid) {
    auto orc = std::make_shared<Orc>("Orc1", 0, 0);
    auto druid = std::make_shared<Druid>("Druid1", 10, 10);
    BattleRuleVisitor visitor;
    ASSERT_TRUE(orc->accept(visitor, *druid));
}

TEST(NPCTest, SquirrelPeaceful) {
    auto squirrel = std::make_shared<Squirrel>("Sq1", 0, 0);
    auto orc = std::make_shared<Orc>("Orc1", 10, 10);
    BattleRuleVisitor visitor;
    ASSERT_FALSE(squirrel->accept(visitor, *orc));
}

TEST(NPCTest, DistanceCheck) {
    auto npc1 = std::make_shared<Orc>("Orc1", 0, 0);
    auto npc2 = std::make_shared<Druid>("Druid1", 100, 0);
    ASSERT_FALSE(npc1->isWithinRange(*npc2, 50));
    ASSERT_TRUE(npc1->isWithinRange(*npc2, 150));
}