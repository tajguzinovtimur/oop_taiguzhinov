#pragma once
#include <string>
#include <map>

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;
const int GAME_DURATION = 30;
const int INITIAL_NPC_COUNT = 50;

enum class NPCType { ORC, SQUIRREL, DRUID };

struct NPCStats {
    int moveDistance;
    int killDistance;
    
    NPCStats(int move, int kill) : moveDistance(move), killDistance(kill) {}
};

const std::map<std::string, NPCStats> NPC_STATS = {
    {"Orc", {20, 10}},
    {"Squirrel", {5, 5}},
    {"Druid", {10, 10}}
};

inline bool canKill(NPCType attacker, NPCType target) {
    if (attacker == NPCType::ORC && target == NPCType::DRUID) return true;
    if (attacker == NPCType::DRUID && target == NPCType::SQUIRREL) return true;
    return false;
}

inline std::string getTypeName(NPCType type) {
    switch (type) {
        case NPCType::ORC: return "Orc";
        case NPCType::SQUIRREL: return "Squirrel";
        case NPCType::DRUID: return "Druid";
        default: return "Unknown";
    }
}