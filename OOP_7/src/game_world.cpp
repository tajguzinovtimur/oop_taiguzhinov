#include "../include/game_world.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>

GameWorld::GameWorld() = default;

GameWorld::~GameWorld() {
    stop();
    if (movementThread.joinable()) movementThread.join();
    if (battleThread.joinable()) battleThread.join();
    if (printerThread.joinable()) printerThread.join();
}

void GameWorld::initialize() {
    npcs = NPCFactory::createInitialNPCs(INITIAL_NPC_COUNT);
    
    int orcs = 0, squirrels = 0, druids = 0;
    for (const auto& npc : npcs) {
        switch (npc->getType()) {
            case NPCType::ORC: orcs++; break;
            case NPCType::SQUIRREL: squirrels++; break;
            case NPCType::DRUID: druids++; break;
        }
    }
    
    std::lock_guard lock(consoleMtx);
    std::cout << "Game initialized with " << npcs.size() << " NPCs\n";
    std::cout << "Orcs: " << orcs << ", Squirrels: " << squirrels 
              << ", Druids: " << druids << "\n";
}

void GameWorld::run() {
    startTime = std::chrono::steady_clock::now();
    running = true;
    
    std::cout << "Starting game...\n";
    
    movementThread = std::thread([this]() { movementLoop(); });
    battleThread = std::thread([this]() { battleLoop(); });
    printerThread = std::thread([this]() { printerLoop(); });
    
    std::this_thread::sleep_for(std::chrono::seconds(GAME_DURATION));
    
    stop();
    std::cout << "\nGame finished!\n";
    
    // Выводим выживших
    auto survivors = getAliveNPCs();
    std::cout << "\n=== SURVIVORS ===\n";
    for (const auto& npc : survivors) {
        std::cout << npc->getName() << " (" << npc->getTypeName() 
                  << ") at (" << npc->getX() << "," << npc->getY() << ")\n";
    }
    std::cout << "Total survivors: " << survivors.size() << "/" << npcs.size() << "\n";
}

void GameWorld::stop() {
    running = false;
    battleCV.notify_all();
}

void GameWorld::movementLoop() {
    while (running.load()) {
        processMovements();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void GameWorld::processMovements() {
    std::shared_lock lock(npcsMtx);
    
    // Двигаем живых NPC
    for (auto& npc : npcs) {
        if (npc->isAlive()) {
            npc->moveRandom();
        }
    }
    
    // Проверяем столкновения
    for (size_t i = 0; i < npcs.size(); ++i) {
        if (!npcs[i]->isAlive()) continue;
        
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (!npcs[j]->isAlive()) continue;
            
            int killDist = std::min(npcs[i]->getKillDistance(), npcs[j]->getKillDistance());
            if (npcs[i]->isWithinRange(*npcs[j], killDist)) {
                if (canKill(npcs[i]->getType(), npcs[j]->getType())) {
                    addBattleToQueue(npcs[i], npcs[j]);
                }
                if (canKill(npcs[j]->getType(), npcs[i]->getType())) {
                    addBattleToQueue(npcs[j], npcs[i]);
                }
            }
        }
    }
}

void GameWorld::battleLoop() {
    while (running.load() || !battleQueue.empty()) {
        std::vector<Battle> localBattles;
        
        {
            std::unique_lock lock(battleQueueMtx);
            battleCV.wait_for(lock, std::chrono::milliseconds(100),
                           [this]() { return !battleQueue.empty() || !running.load(); });
            
            if (!battleQueue.empty()) {
                localBattles.swap(battleQueue);
            }
        }
        
        for (const auto& battle : localBattles) {
            if (!battle.attacker->isAlive() || !battle.target->isAlive()) {
                continue;
            }
            
            if (!canKill(battle.attacker->getType(), battle.target->getType())) {
                continue;
            }
            
            int attack = NPC::rollDice();
            int defense = NPC::rollDice();
            
            {
                std::lock_guard lock(consoleMtx);
                std::cout << battle.attacker->getName() << "(" << attack 
                          << ") vs " << battle.target->getName() << "(" 
                          << defense << "): ";
            }
            
            if (attack > defense) {
                battle.target->kill();
                std::lock_guard lock(consoleMtx);
                std::cout << battle.target->getName() << " killed!\n";
            } else {
                std::lock_guard lock(consoleMtx);
                std::cout << "miss\n";
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void GameWorld::printerLoop() {
    int iteration = 0;
    
    while (running.load()) {
        printGameState(iteration++);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void GameWorld::printGameState(int iteration) {
    auto aliveNPCs = getAliveNPCs();
    
    std::lock_guard lock(consoleMtx);
    
    // Очистка экрана
    std::cout << "\033[2J\033[1;1H";
    
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    
    std::cout << "=== DUNGEON EDITOR (Variant 1) ===\n";
    std::cout << "Time: " << elapsed << "/" << GAME_DURATION << "s | ";
    std::cout << "Iteration: " << iteration << " | ";
    std::cout << "Alive: " << aliveNPCs.size() << "/" << npcs.size() << "\n";
    std::cout << "=================================\n";
    
    // Статистика
    int orcs = 0, squirrels = 0, druids = 0;
    for (const auto& npc : aliveNPCs) {
        switch (npc->getType()) {
            case NPCType::ORC: orcs++; break;
            case NPCType::SQUIRREL: squirrels++; break;
            case NPCType::DRUID: druids++; break;
        }
    }
    
    std::cout << "Orcs: " << orcs << ", Squirrels: " << squirrels 
              << ", Druids: " << druids << "\n\n";
    
    // Простая карта 40x20
    const int DISPLAY_WIDTH = 40;
    const int DISPLAY_HEIGHT = 20;
    std::vector<std::vector<char>> map(DISPLAY_HEIGHT, 
                                       std::vector<char>(DISPLAY_WIDTH, '.'));
    
    for (const auto& npc : aliveNPCs) {
        int x = (npc->getX() * DISPLAY_WIDTH) / MAP_WIDTH;
        int y = (npc->getY() * DISPLAY_HEIGHT) / MAP_HEIGHT;
        
        if (x >= 0 && x < DISPLAY_WIDTH && y >= 0 && y < DISPLAY_HEIGHT) {
            char symbol = '.';
            switch (npc->getType()) {
                case NPCType::ORC: symbol = 'O'; break;
                case NPCType::SQUIRREL: symbol = 'S'; break;
                case NPCType::DRUID: symbol = 'D'; break;
            }
            map[y][x] = symbol;
        }
    }
    
    // Вывод карты
    for (const auto& row : map) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }
    
    std::cout << "\nO=Orc, S=Squirrel, D=Druid, .=empty\n";
}

void GameWorld::addBattleToQueue(std::shared_ptr<NPC> attacker, 
                                std::shared_ptr<NPC> target) {
    std::lock_guard lock(battleQueueMtx);
    battleQueue.push_back({attacker, target});
    battleCV.notify_one();
}

std::vector<std::shared_ptr<NPC>> GameWorld::getAliveNPCs() const {
    std::vector<std::shared_ptr<NPC>> alive;
    std::shared_lock lock(npcsMtx);
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            alive.push_back(npc);
        }
    }
    
    return alive;
}