// Entity.cpp
#include "Entity.h"

const std::string& Entity::getName() const { return name; }
int Entity::getHealth() const { return health; }
bool Entity::isAlive() const { return health > 0; }

// Implementation of the takeDamage method
void Entity::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << " took " << damage << " damage! Health remaining: " << health << std::endl;
}

// Implementation of the destructor
Entity::~Entity() {}