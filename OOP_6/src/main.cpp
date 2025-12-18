#include "DungeonEditor.hpp"
#include "Observer.hpp"
#include <iostream>

int main() {
    DungeonEditor editor;

    editor.addObserver(std::make_shared<ConsoleObserver>());
    editor.addObserver(std::make_shared<FileObserver>("log.txt"));

    editor.addNPC(NPCType::ORC, "Grom", 100, 100);
    editor.addNPC(NPCType::DRUID, "Filius", 150, 150);
    editor.addNPC(NPCType::SQUIRREL, "Nutty", 120, 120);
    editor.addNPC(NPCType::ORC, "Ugluk", 130, 130);

    std::cout << "=== All NPCs ===" << std::endl;
    editor.printAll();

    editor.saveToFile("data/npcs.txt");

    std::cout << "\n=== Battle (range=50) ===" << std::endl;
    editor.battle(50);

    std::cout << "\n=== Survivors ===" << std::endl;
    editor.printAll();

    return 0;
}