#pragma once
#include <vector>
#include <iostream>
#include "Weapon.h"
#include "HealPotion.h"

class Inventory {
private:
    std::vector<Weapon> items;
    int equippedIndex = -1;
    int healPotions = 0;
    static const int MAX_POTIONS = 6;

public:
    Inventory() : healPotions(0) {}

    void addWeapon(const Weapon& w) { items.push_back(w); if (equippedIndex == -1) equippedIndex = 0; }
    
    void listWeapons() const {
        if (items.empty()) { std::cout << "Inventory empty.\n"; return; }
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i+1 << ") " << items[i].name << " (+" << items[i].damageBonus << " dmg)\n";
        }
    }

    bool equip(int idx) {
        if (idx < 1 || idx > (int)items.size()) return false;
        equippedIndex = idx - 1;
        return true;
    }

    int getEquippedBonus() const {
        if (equippedIndex < 0 || equippedIndex >= (int)items.size()) return 0;
        return items[equippedIndex].damageBonus;
    }

    const Weapon* getEquipped() const {
        if (equippedIndex < 0 || equippedIndex >= (int)items.size()) return nullptr;
        return &items[equippedIndex];
    }

    // Heal Potion methods
    bool addHealPotion() {
        if (healPotions >= MAX_POTIONS) {
            std::cout << "Cannot carry more than " << MAX_POTIONS << " heal potions!\n";
            return false;
        }
        healPotions++;
        return true;
    }

    bool useHealPotion() {
        if (healPotions <= 0) {
            std::cout << "No heal potions available!\n";
            return false;
        }
        healPotions--;
        return true;
    }

    int getHealPotionCount() const {
        return healPotions;
    }

    void showInventoryStatus() const {
        std::cout << "\nInventory Status:\n";
        std::cout << "Heal Potions: " << healPotions << "/" << MAX_POTIONS 
                  << " (Heals " << HealPotion::HEAL_AMOUNT << " HP each)\n";
        if (!items.empty()) {
            std::cout << "Weapons:\n";
            listWeapons();
        }
    }
};

