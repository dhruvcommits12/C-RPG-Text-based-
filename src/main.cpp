// filepath: c:\Users\Dhruv\OneDrive\Desktop\RPG game\main.cpp
// main.cpp
#include "Game.h"
#include <iostream>
#include <string>

int main() {

    std::cout << "Enter your character name: ";
    std::string name;
    std::getline(std::cin, name);
    if (name.empty()) name = "Hero";

    // The Game object manages the entire game state, map, and player.

    Game myGame(name); 
    
    // Start the game loop
    myGame.startLoop();
    
    return 0;
}
