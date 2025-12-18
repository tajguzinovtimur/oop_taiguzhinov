#pragma once
#include "constants.hpp"
#include <string>
#include <memory>
#include <mutex>
#include <atomic>

class NPC {
private:
    mutable std::mutex mtx;
    NPCType type;
    std::string name;
    int x, y;
    std::atomic<bool> alive{true};
    int id;
    
    static std::atomic<int> nextId;
    
public:
    NPC(NPCType type, const std::string& name, int x, int y);
    virtual ~NPC() = default;
    
    NPC(const NPC&) = delete;
    NPC& operator=(const NPC&) = delete;
    
    NPCType getType() const;
    std::string getName() const;
    std::string getTypeName() const;
    int getX() const;
    int getY() const;
    bool isAlive() const;
    int getId() const;
    
    void setPosition(int newX, int newY);
    void kill();
    
    bool isWithinRange(const NPC& other, int range) const;
    void moveRandom();
    
    static int rollDice();
    
    int getMoveDistance() const;
    int getKillDistance() const;
};