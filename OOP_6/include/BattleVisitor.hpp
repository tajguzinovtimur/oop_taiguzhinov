#ifndef BATTLEVISITOR_HPP
#define BATTLEVISITOR_HPP

#include "NPC.hpp"

class Orc;
class Squirrel;
class Druid;

class BattleVisitor {
public:
    virtual bool visit(Orc& orc, NPC& other) = 0;
    virtual bool visit(Squirrel& squirrel, NPC& other) = 0;
    virtual bool visit(Druid& druid, NPC& other) = 0;
};

class BattleRuleVisitor : public BattleVisitor {
public:
    bool visit(Orc& orc, NPC& other) override;
    bool visit(Squirrel& squirrel, NPC& other) override;
    bool visit(Druid& druid, NPC& other) override;
};

#endif