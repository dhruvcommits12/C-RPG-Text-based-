#pragma once
#include <iostream>

class Coins {
private:
    int amount;
public:
    Coins(int start = 0) : amount(start) {}
    int get() const { return amount; }  
    void add(int n) { amount += n; }  
    bool spend(int n) {          
        if (n <= 0) return true;
        if (amount >= n) { amount -= n; return true; }
        return false;
    }
    void set(int n) { amount = n; }  
};
