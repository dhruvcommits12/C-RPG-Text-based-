#pragma once
#include <map>
#include <vector>
#include <sstream>
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Weapon.h"

// Simple forward declaration for Room.
class Room {
private:
    std::string description;
    std::map<std::string, int> exits; 
    std::vector<Monster*> monsters; 
    
public:
    Room(const std::string& desc) : description(desc) {}
    ~Room() { for (auto m : monsters) delete m; }

    void addExit(const std::string& direction, int nextRoomID) {
        exits[direction] = nextRoomID;
    }
    
    void addMonster(Monster* m) {
        monsters.push_back(m);
    }

    void displayInfo() const {
        std::cout << "\n===========================================\n";
        std::cout << description << std::endl;
        std::cout << "Exits: ";
        for (const auto& pair : exits) {
            std::cout << "[" << pair.first << "] ";
        }
        std::cout << "\nMonsters Present: " << monsters.size() << std::endl;
        for (size_t i = 0; i < monsters.size(); ++i) {
            std::cout << i + 1 << ") " << monsters[i]->getName() 
                     << " (HP: " << monsters[i]->getHealth() << ")" << std::endl;
        }
        std::cout << "===========================================\n";
    }
   
    
    int getExitID(const std::string& direction) const {
        if (exits.count(direction)) {
            return exits.at(direction);
        }
        return -1; 
    }
    
    std::vector<Monster*>& getMonsters() { return monsters; }

     std::vector<std::string> getDirections() const {
        std::vector<std::string> dirs;
        for (const auto& p : exits) dirs.push_back(p.first);
        return dirs;
    }
};


class Game {
private:
    std::map<int, Room*> worldMap;
    Player* player;
    int currentRoomID;
    bool isRunning;

    std::vector<Weapon> shopItems; 

    void processCommand(const std::string& command);
    void handleMove(const std::string& direction);
    void handleAttack();
    void handleStatus() const;
    void setupMap();
    void handleFlee();
    void handleBuy(const std::string& arg);

public:
    Game() : Game("Hero") {}
    Game(const std::string& playerName) 
        : player(new Player(playerName)), currentRoomID(1), isRunning(true) {
        srand(time(0));
        setupMap();
    }

    ~Game() {
        delete player;
        for (auto const&entry : worldMap) delete entry.second;
    }

    void startLoop();
};

