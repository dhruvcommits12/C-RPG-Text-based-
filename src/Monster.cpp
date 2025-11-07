// Monster.cpp
#include "Monster.h"

// Implementations for Monster methods

Monster::Monster(const std::string& n, int h, int s, int xp, int diffLevel)
    : Entity(n, h, s), xpValue(xp), difficultyLevel(diffLevel) {}

void Monster::attack(Entity* target) {
    if (!target || !isAlive()) return;
    
    int base_damage = strength + difficultyLevel;
    
    // Simple damage randomization (e.g., +/- 10%)
    int min_damage = base_damage ;
    int max_damage = base_damage * 1.2;
    int damage = min_damage + (std::rand() % (max_damage - min_damage + 1));
    std::cout << name << " lunges at " << target->getName() << " for " << damage << " damage!" << std::endl;
    target->takeDamage(damage);
}

int Monster::getXPValue() const {
    return xpValue;
}

int Monster::getDifficultyLevel() const {
    return difficultyLevel;
}

