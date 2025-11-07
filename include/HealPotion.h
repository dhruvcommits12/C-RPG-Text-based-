#pragma once
#include <string>

class HealPotion {
public:
    static const int HEAL_AMOUNT = 25;
    static const int COST = 20;
    
    HealPotion() = default;
    
    static std::string getName() { return "Heal Potion"; }
    static int getHealAmount() { return HEAL_AMOUNT; }
    static int getCost() { return COST; }
};