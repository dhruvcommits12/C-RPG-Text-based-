// filepath: c:\Users\Dhruv\OneDrive\Desktop\RPG game\Monster.h
#include "Entity.h"
#include <bits/stdc++.h>

class Monster : public Entity {
private:
    int xpValue;
    int difficultyLevel; // difficulty level of the monster

public:
    // Allow construction with 4 args (difficulty defaults to 0)
    Monster(const std::string& n, int h, int s, int xp, int diffLevel = 0);

    // Declaration only (implementation in Monster.cpp)
    void attack(Entity* target) override;

    int getXPValue() const;
    int getDifficultyLevel() const;
};