
#include "Entity.h"
#include <bits/stdc++.h>
#include "Inventory.h"
#include "Coins.h"

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
};
    

