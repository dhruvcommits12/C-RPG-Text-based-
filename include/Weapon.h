#pragma once
#include <string>

class Weapon {
public:
    std::string name;
    int damageBonus;
    int cost;

    Weapon() : name("fist"), damageBonus(0), cost(0) {}
    Weapon(const std::string& n, int db, int c) : name(n), damageBonus(db), cost(c) {}
};