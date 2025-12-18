#pragma once
#include "npc.hpp"
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <shared_mutex>
#include <random>

class NPCFactory {
private:
    static inline std::random_device rd;
    static inline std::mt19937 gen{rd()};
    static inline std::uniform_int_distribution<> nameDist{1, 999};
    static inline std::uniform_int_distribution<> coordDist{0, MAP_WIDTH-1};
    static inline std::uniform_int_distribution<> typeDist{0, 2};
    
public:
    static std::shared_ptr<NPC> createNPC(NPCType type) {
        std::string name;
        switch (type) {
            case NPCType::ORC:
                name = "Orc_" + std::to_string(nameDist(gen));
                break;
            case NPCType::SQUIRREL:
                name = "Squirrel_" + std::to_string(nameDist(gen));
                break;
            case NPCType::DRUID:
                name = "Druid_" + std::to_string(nameDist(gen));
                break;
        }
        
        int x = coordDist(gen);
        int y = coordDist(gen);
        
        return std::make_shared<NPC>(type, name, x, y);
    }
    
    static std::shared_ptr<NPC> createRandomNPC() {
        NPCType type = static_cast<NPCType>(typeDist(gen));
        return createNPC(type);
    }
    
    static std::vector<std::shared_ptr<NPC>> createInitialNPCs(int count) {
        std::vector<std::shared_ptr<NPC>> npcs;
        npcs.reserve(count);
        
        for (int i = 0; i < count; ++i) {
            npcs.push_back(createRandomNPC());
        }
        
        return npcs;
    }
};

class GameWorld {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    mutable std::shared_mutex npcsMtx;
    
    std::thread movementThread;
    std::thread battleThread;
    std::thread printerThread;
    
    std::atomic<bool> running{false};
    std::mutex consoleMtx;
    
    struct Battle {
        std::shared_ptr<NPC> attacker;
        std::shared_ptr<NPC> target;
    };
    std::vector<Battle> battleQueue;
    std::mutex battleQueueMtx;
    std::condition_variable battleCV;
    
    std::chrono::steady_clock::time_point startTime;
    
    void processMovements();
    void processBattles();
    void printGameState(int iteration);
    
public:
    GameWorld();
    ~GameWorld();
    
    void initialize();
    void run();
    void stop();
    
    void addBattleToQueue(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> target);
    std::vector<std::shared_ptr<NPC>> getAliveNPCs() const;
    
private:
    void movementLoop();
    void battleLoop();
    void printerLoop();
};