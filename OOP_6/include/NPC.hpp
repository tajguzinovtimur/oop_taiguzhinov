#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <memory>


enum class NPCType {
    ORC,
    SQUIRREL,
    DRUID
};

class NPC;
class BattleVisitor;

class NPC {
protected:
    NPCType type;
    std::string name;
    int x, y;

public:
    NPC(NPCType type, const std::string& name, int x, int y);
    virtual ~NPC() = default;

    NPCType getType() const;
    std::string getName() const;
    int getX() const;
    int getY() const;

    virtual bool accept(BattleVisitor& visitor, NPC& other) = 0;
    virtual std::string getTypeName() const = 0;
    virtual void print() const;

    bool isWithinRange(const NPC& other, int range) const;
};

class Orc : public NPC {
public:
    Orc(const std::string& name, int x, int y);
    bool accept(BattleVisitor& visitor, NPC& other) override;
    std::string getTypeName() const override;
};


class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, int x, int y);
    bool accept(BattleVisitor& visitor, NPC& other) override;
    std::string getTypeName() const override;
};


class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y);
    bool accept(BattleVisitor& visitor, NPC& other) override;
    std::string getTypeName() const override;
};
#endif