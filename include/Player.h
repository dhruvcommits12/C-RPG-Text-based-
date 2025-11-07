
#include "Entity.h"
#include <bits/stdc++.h>
#include "Inventory.h"
#include "Coins.h"
#include "HealPotion.h"

class Player : public Entity {
private:
    int level;
    int currentXP;
    Inventory inventory;
    Coins coins;
public:
    Player(const std::string& n)
        : Entity(n, 100, 15), level(1), currentXP(0), inventory(), coins(40 /*start coins*/) {} //Constructor passing for both the current and base class

    void attack(Entity* target) override; // These are from my Entity class functions
    void takeDamage(int damage) override; //  Same here
    void gainXP(int amount);
    Inventory& getInventory() { return inventory; }
    Coins& getCoins() { return coins; }

    int getLevel() const { return level; }
    
    bool buyHealPotion() {
        if (coins.get() >= HealPotion::COST) {
            if (inventory.addHealPotion()) {
                coins.spend(HealPotion::COST);
                std::cout << "Bought a heal potion for " << HealPotion::COST << " coins.\n";
                return true;
            }
        } else {
            std::cout << "Not enough coins to buy a heal potion!\n";
        }
        return false;
    }

    bool useHealPotion() {
        if (inventory.useHealPotion()) {
            // Since Entity class has base health of 100, we'll use that as max
            const int MAX_HEALTH = 100;
            health = health + HealPotion::HEAL_AMOUNT;

            if(health > MAX_HEALTH){

                health = MAX_HEALTH;
                std::cout << name << " used a heal potion... but health was already full! The potion was wasted.\n";
            return true;  // still return true because the potion was consumed
            }
            else{
            std::cout << name << " used a heal potion and recovered " << HealPotion::HEAL_AMOUNT << " HP!\n";
            return true;
            }
        }
        return false;
    }
};
    

