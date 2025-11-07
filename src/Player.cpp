// Player.cpp
#include "Player.h"

// Implementing the attack method for the Player class

void Player::attack(Entity* target) {
    int weaponBonus = inventory.getEquippedBonus();
    int damage = strength + (level * 2) + weaponBonus;
    std::cout << name << " strikes " << target->getName() << " with " << damage << " damage!" << std::endl;
    target->takeDamage(damage);
}

// Implementing the gainXP method for the Player class
void Player::gainXP(int amount) {
    currentXP += amount;
    std::cout << name << " gained " << amount << " XP. ";
    // Simple level-up logic
    if (currentXP >= level * 80) {
        level++;
        strength += 5;
        health = health*0.8 + (level * 20); // Heals and increases max health
        currentXP = 0;
        std::cout << "LEVEL UP! Now Level " << level << "!" << std::endl;
    }
}

void Player::takeDamage(int damage) {
    Entity::takeDamage(damage);
    // optional: extra player-specific behavior
    std::cout << getName() << " now has " << getHealth() << " HP." << std::endl;
}