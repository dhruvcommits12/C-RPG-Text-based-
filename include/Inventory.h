#pragma once
#include <vector>
#include <iostream>
#include "Weapon.h"

class Inventory {
private:
    std::vector<Weapon> items;
    int equippedIndex = -1;
public:
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
};

