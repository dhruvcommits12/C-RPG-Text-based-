#pragma once
#include <string>
#include <iostream>
#include <cstdlib> // For simple random damage in Monster

class Entity {
protected:
    std::string name;
    int health;
    int strength;

public:
    Entity(const std::string& n, int h, int s)
        : name(n), health(h), strength(s) {}
        
    virtual ~Entity();

    // PURE VIRTUAL FUNCTION: Makes Entity abstract and forces derived classes to implement
    virtual void attack(Entity* target) = 0; 

    // VIRTUAL FUNCTION: Can be overridden, but has a default implementation
    virtual void takeDamage(int damage) ;

    // Accessors (Encapsulation)
    const std::string& getName() const;
    int getHealth() const;
    virtual bool isAlive() const;
    
    
};