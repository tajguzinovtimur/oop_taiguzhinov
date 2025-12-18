#include "../include/npc.hpp"
#include <random>
#include <cmath>
#include <sstream>

// Определение статической переменной
std::atomic<int> NPC::nextId(0);

NPC::NPC(NPCType type, const std::string& name, int x, int y)
    : type(type), name(name), x(x), y(y), id(nextId++) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        throw std::out_of_range("NPC coordinates out of map bounds");
    }
}

NPCType NPC::getType() const {
    std::lock_guard<std::mutex> lock(mtx);
    return type;
}

std::string NPC::getName() const {
    std::lock_guard<std::mutex> lock(mtx);
    return name;
}

std::string NPC::getTypeName() const {
    return ::getTypeName(type);
}

int NPC::getX() const {
    std::lock_guard<std::mutex> lock(mtx);
    return x;
}

int NPC::getY() const {
    std::lock_guard<std::mutex> lock(mtx);
    return y;
}

bool NPC::isAlive() const {
    return alive.load();
}

int NPC::getId() const {
    return id;
}

void NPC::setPosition(int newX, int newY) {
    std::lock_guard<std::mutex> lock(mtx);
    
    if (newX < 0) newX = 0;
    if (newX >= MAP_WIDTH) newX = MAP_WIDTH - 1;
    if (newY < 0) newY = 0;
    if (newY >= MAP_HEIGHT) newY = MAP_HEIGHT - 1;
    
    x = newX;
    y = newY;
}

void NPC::kill() {
    alive.store(false);
}

bool NPC::isWithinRange(const NPC& other, int range) const {
    int dx = getX() - other.getX();
    int dy = getY() - other.getY();
    int distanceSquared = dx * dx + dy * dy;
    return distanceSquared <= (range * range);
}

void NPC::moveRandom() {
    if (!isAlive()) return;
    
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    std::uniform_int_distribution<> dirDist(-1, 1);
    std::uniform_int_distribution<> distDist(1, getMoveDistance());
    
    int moveDist = distDist(gen);
    int dx = dirDist(gen);
    int dy = dirDist(gen);
    
    if (dx == 0 && dy == 0) return;
    
    int newX = getX() + dx * moveDist;
    int newY = getY() + dy * moveDist;
    
    setPosition(newX, newY);
}

int NPC::rollDice() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    std::uniform_int_distribution<> diceDist(1, 6);
    return diceDist(gen);
}

int NPC::getMoveDistance() const {
    auto it = NPC_STATS.find(getTypeName());
    if (it != NPC_STATS.end()) {
        return it->second.moveDistance;
    }
    return 10;
}

int NPC::getKillDistance() const {
    auto it = NPC_STATS.find(getTypeName());
    if (it != NPC_STATS.end()) {
        return it->second.killDistance;
    }
    return 10;
}