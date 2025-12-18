#include "../include/game_world.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "=== Dungeon Editor Async ===\n";
        std::cout << "Variant 1: Orc, Squirrel, Druid\n";
        std::cout << "Rules: Orcs kill Druids, Druids kill Squirrels\n";
        std::cout << "Map: " << MAP_WIDTH << "x" << MAP_HEIGHT << "\n";
        std::cout << "Game duration: " << GAME_DURATION << " seconds\n";
        std::cout << "Initial NPCs: " << INITIAL_NPC_COUNT << "\n";
        std::cout << "============================\n\n";
        
        GameWorld world;
        world.initialize();
        world.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}