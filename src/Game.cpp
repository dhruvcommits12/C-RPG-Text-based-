// ...existing code...
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

void Game::setupMap() {

    shopItems.push_back(Weapon("Iron Sword", 5, 50));
    shopItems.push_back(Weapon("Steel Axe", 10, 110));
    shopItems.push_back(Weapon("Magic Staff", 15, 160));
    Room* r1 = new Room("You entered the arena of Monsters.. Beware!.. You may check the shop");
    r1->addExit("north", 2);
    worldMap[1] = r1;


    Room* r2 = new Room("This is a forest path. You may hear something moving. It's not the ants.. its the GOBLINS");
    r2->addExit("north", 3);
    r2->addExit("south", 1);
    r2->addExit("east", 4);
    r2->addExit("west", 6);
    r2->addMonster(new Monster("Goblin", 30, 8, 10));
    worldMap[2] = r2;
    worldMap[2]->addMonster(new Monster("Goblin Giant", 35, 9, 12, 2));


    Room* r3 = new Room("You have entered the realm of wizards.. beware of their spells");
    r3->addExit("south", 2);
    r3->addExit("east", 4);
    r3->addMonster(new Monster("Evil Wizard", 100, 20, 50));
    worldMap[3] = r3;

    Room* r4 = new Room("This is a dark cave. But remember what's hiding in the dark");
    r4->addExit("west", 2);
    r4->addExit("east", 5);
    r4->addMonster(new Monster("Mighty Miner", 50,20 , 22));
    worldMap[4] = r4;
    worldMap[4]->addMonster(new Monster("Bat Swarm", 21, 6, 8));

    Room* r5 = new Room("These are old ruins covered in plants. Beware.. the legend goes that here the undead lives");
    r5->addExit("west", 4);
    r5->addMonster(new Monster("Skeleton Warrior", 40, 10, 15 ,2));
    worldMap[5] = r5;

    Room* r6 = new Room("This is the realm of souls.. don't wait for long it would piss the spirit empress of");
    r6->addExit("east", 2);
    r6->addExit("north", 7);
    r6->addMonster(new Monster("Spirit Emperess", 20, 22 ,20));
    worldMap[6] = r6;

    Room* r7 = new Room("It's the MONK.. the evil man who created these monsters.. you sure wanna stay here for long?.. he might turn you into one too");
    r7->addExit("south", 6);
    r7->addMonster(new Monster("Monk", 170, 35, 100, 5));
    worldMap[7] = r7;
}

void Game::handleFlee() {
    Room* cur = worldMap[currentRoomID];
    auto dirs = cur->getDirections();
    if (dirs.empty()) {
        std::cout << "No way to run from here." << std::endl;
        return;
    }
    std::string chosen = dirs[std::rand() % dirs.size()];
    int next = cur->getExitID(chosen);
    if (next == -1) {
        std::cout << "You could not run." << std::endl;
        return;
    }
    std::cout << "You run " << chosen << "." << std::endl;
    currentRoomID = next;
    std::cout << "You entered a new room." << std::endl;
    worldMap[currentRoomID]->displayInfo();
}
void Game::handleBuy(const std::string& arg) {
    // Remove room check to allow shopping anywhere
    if (arg.empty() || arg == "list") {
        std::cout << "\n=== Available Items ===\n";
        // List weapons
        std::cout << "=== Weapons ===\n";
        for (size_t i = 0; i < shopItems.size(); ++i) {
            std::cout << i+1 << ") " << shopItems[i].name 
                     << " (+" << shopItems[i].damageBonus << " dmg) - " 
                     << shopItems[i].cost << " coins\n";
        }
        // List heal potions
        std::cout << "\n=== Potions ===\n";
        std::cout << (shopItems.size() + 1) << ") Heal Potion"
                 << " (+" << HealPotion::HEAL_AMOUNT << " HP) - " 
                 << HealPotion::COST << " coins\n";
        
        std::cout << "\nYou have " << player->getCoins().get() << " coins."
                 << "\nUse: buy <number> to purchase\n";
        return;
    }

    // Try parse index
    int idx = 0;
    try {
        idx = std::stoi(arg);
    } catch(...) {
        std::cout << "Invalid item number.\n";
        return;
    }
    
    // Check if buying a heal potion
    if (idx == shopItems.size() + 1) {
        player->buyHealPotion();
        return;
    }

    if (idx < 1 || idx > (int)shopItems.size()) {
        std::cout << "Invalid item number.\n";
        return;
    }

    Weapon chosen = shopItems[idx-1];
    if (player->getCoins().spend(chosen.cost)) {
        player->getInventory().addWeapon(chosen);
        std::cout << "Purchased " << chosen.name << "! Added to inventory.\n";
    } else {
        std::cout << "Not enough coins. You have " << player->getCoins().get() 
                 << " coins but need " << chosen.cost << ".\n";
    }
}


void Game::processCommand(const std::string& input) {
    std::stringstream ss(input);
    std::string verb, noun;
    ss >> verb >> noun;

    if (verb == "move") handleMove(noun);
    else if (verb == "attack") handleAttack();
    else if (verb == "status") handleStatus();
    else if (verb == "flee") handleFlee();
    else if (verb == "buy") handleBuy(noun);
    else if (verb == "heal") {
        player->useHealPotion();
    }
    else if (verb == "equip") {

         if (noun.empty()) {
            std::cout << "Usage: equip <inventory-number>\n";
            return;
        }
        int idx = std::stoi(noun);
        if (player->getInventory().equip(idx)) {
            std::cout << "Equipped item " << idx << std::endl;
        } else {
            std::cout << "Invalid equip index.\n";
        }
    }

    else if (verb == "quit" || verb == "exit") isRunning = false;
    else std::cout << "Unknown command. Try: move [direction], attack, flee, buy, equip, heal, status, quit.\n";
}

void Game::handleAttack() {
    Room* currentRoom = worldMap[currentRoomID];
    auto& monsters = currentRoom->getMonsters();
    
    if (monsters.empty()) {
        std::cout << "Nothing to attack here.\n";
        return;
    }

    Monster* target = nullptr;
    
    // If only one monster, attack it directly
    if (monsters.size() == 1) {
        target = monsters[0];
        std::cout << "Attacking " << target->getName() 
                 << " (HP: " << target->getHealth() << ")\n";
    } else {
        // Multiple monsters - let player choose
        std::cout << "\nChoose your target:\n";
        for (size_t i = 0; i < monsters.size(); ++i) {
            std::cout << i + 1 << ") " << monsters[i]->getName() 
                     << " (HP: " << monsters[i]->getHealth() << ")\n";
        }

        int choice;
        std::cout << "Enter target number (1-" << monsters.size() << "): ";
        std::string input;
        std::getline(std::cin, input);
        try {
            choice = std::stoi(input);
        } catch(...) {
            std::cout << "Invalid choice.\n";
            return;
        }

        if (choice < 1 || choice > (int)monsters.size()) {
            std::cout << "Invalid target number.\n";
            return;
        }

        target = monsters[choice - 1];
    }

    // Attack the chosen/only monster
    player->attack(target);

    // Handle monster death and rewards
    if (!target->isAlive()) {
        int xpValue = target->getXPValue();
        player->gainXP(xpValue);
        player->getCoins().add(xpValue);
        std::cout << "You defeated " << target->getName() << "!\n";
        std::cout << "Gained " << xpValue << " XP and coins!\n";
        
        // Remove and delete the dead monster
        auto it = std::find(monsters.begin(), monsters.end(), target);
        if (it != monsters.end()) {
            monsters.erase(it);
        }
        delete target;

        // Check victory condition
        if (currentRoomID == 7 && monsters.empty()) {
            std::cout << "\n*** Congratulations! You have defeated the final boss! ***\n";
            isRunning = false;
        }
        return;
    }

    // All surviving monsters counter-attack
    std::cout << "\nThe monsters counter-attack!\n";
    for (auto* monster : monsters) {
        if (monster->isAlive()) {
            monster->attack(player);
            if (!player->isAlive()) break;
        }
    }
}

void Game::handleMove(const std::string& direction) {
    Room* cur = nullptr;
    if (worldMap.count(currentRoomID)) cur = worldMap[currentRoomID];
    if (!cur) { std::cout << "You are lost.\n"; return; }

    int next = cur->getExitID(direction);
    if (next == -1) {
        std::cout << "You can't go " << direction << " from here.\n";
        return;
    }

    currentRoomID = next;
    std::cout << "You move " << direction << ".\n";
    if (worldMap.count(currentRoomID)) worldMap[currentRoomID]->displayInfo();
}


void Game::handleStatus() const {
    std::cout << "\n=== " << player->getName() << "'s Status ===" << std::endl;
    std::cout << "Health: " << player->getHealth() << std::endl;
    std::cout << "Level: " << player->getLevel() << std::endl;
    std::cout << "Coins: " << player->getCoins().get() << std::endl;
    
    // Show equipped weapon if any
    const Weapon* equipped = player->getInventory().getEquipped();
    std::cout << "Weapon: " << (equipped ? equipped->name : "none") 
              << (equipped ? " (+" + std::to_string(equipped->damageBonus) + " damage)" : "") 
              << std::endl;
    
    std::cout << "\nInventory:" << std::endl;
    player->getInventory().listWeapons();
    std::cout << "====================\n" << std::endl;
}

// ----------------- Leaderboard & persistence (added) -----------------
// Stores and shows a leaderboard in Data.txt using format: name level coins
// Only the current player's record is updated when the game ends.

namespace {
struct LeaderRecord {
    std::string name;
    int level = 0;
    int coins = 0;
};

bool parseRecordLine(const std::string& line, LeaderRecord& out) {
    if (line.empty()) return false;
    std::istringstream iss(line);
    if (!(iss >> out.name >> out.level >> out.coins)) return false;
    return true;
}

std::vector<LeaderRecord> readAllRecords(const std::string& filename) {
    std::vector<LeaderRecord> list;
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return list;
    std::string line;
    while (std::getline(ifs, line)) {
        LeaderRecord r;
        if (parseRecordLine(line, r)) list.push_back(r);
    }
    return list;
}

bool writeAllRecords(const std::string& filename, const std::vector<LeaderRecord>& list) {
    std::ofstream ofs(filename, std::ofstream::trunc);
    if (!ofs.is_open()) return false;
    for (const auto& r : list) {
        ofs << r.name << " " << r.level << " " << r.coins << "\n";
    }
    return true;
}

// Primary sort: higher level first, then higher coins
bool leaderCompare(const LeaderRecord& a, const LeaderRecord& b) {
    if (a.level != b.level) return a.level > b.level;
    return a.coins > b.coins;
}

void updateOrInsertCurrent(std::vector<LeaderRecord>& list, const LeaderRecord& current) {
    for (auto &r : list) {
        if (r.name == current.name) {
            r.level = current.level;
            r.coins = current.coins;
            return;
        }
    }
    list.push_back(current);
}

void displayLeaderboard(const std::vector<LeaderRecord>& sorted) {
    std::cout << "\n=== Leaderboard ===\n";
    if (sorted.empty()) {
        std::cout << "No records.\n";
        std::cout << "===================\n";
        return;
    }

    int rank = 1;
    int lastLevel = sorted[0].level;
    int lastCoins = sorted[0].coins;
    for (size_t i = 0; i < sorted.size(); ++i) {
        const auto &r = sorted[i];
        if (i > 0) {
            if (r.level != lastLevel || r.coins != lastCoins) {
                rank = static_cast<int>(i) + 1;
                lastLevel = r.level;
                lastCoins = r.coins;
            }
        }
        std::cout << rank << ". " << r.name << " | Level: " << r.level << " | Coins: " << r.coins << "\n";
    }
    std::cout << "===================\n";
}
} // anonymous namespace

// Use non-const Player* because getCoins() may return a non-const reference.
void showAndSaveLeaderboardForCurrentPlayer(Player* p) {
    const std::string filename = "Data.txt";
    if (!p) return;
    LeaderRecord current { p->getName(), p->getLevel(), p->getCoins().get() };

    auto records = readAllRecords(filename);
    updateOrInsertCurrent(records, current);
    if (!writeAllRecords(filename, records)) {
        std::cerr << "Warning: failed to save leaderboard to " << filename << "\n";
    }

    std::sort(records.begin(), records.end(), leaderCompare);
    displayLeaderboard(records);
}
// ----------------- end leaderboard -----------------------------------

void Game::startLoop() {
    std::cout << "Welcome to the C++ based RPG.. QUEST OF THE ETERNAL HERO" << std::endl;
    std::cout << "Commands: move [direction], attack, flee, status, quit, buy, equip" << std::endl;

    while (isRunning && player->isAlive()) {
        if (worldMap.count(currentRoomID))
            worldMap[currentRoomID]->displayInfo();
        else
            std::cout << "You are in an unknown area." << std::endl;

        std::cout << "\nYour move: ";
        std::string input;
        if (!std::getline(std::cin, input)) break;
        if (input.empty()) continue;

        processCommand(input);
    }

    if (!player->isAlive()) std::cout << "\nYou have fallen. Game over." << std::endl;
    else std::cout << "\nExiting game." << std::endl;

    // Show leaderboard after the game ends and save current player's final stats.
    showAndSaveLeaderboardForCurrentPlayer(player);
}