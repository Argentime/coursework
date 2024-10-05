#pragma once
#include "functions.h"

class Character {
protected:
    std::string name;
    int health;
    int focus;
    int money;

public:
    Character(std::string name, int hp, int foc, int cash)
        : name(name), health(hp), focus(foc), money(cash) {}

    ~Character() = default;

    virtual void displayStats() const {
        std::cout << "Health: " << health << "\n"
            << "Focus: " << focus << "\n"
            << "Money: " << money << "\n";
    }

    virtual void takeDamage(int dmg) {
        health = (health - dmg > 0) ? health - dmg : 0;
    }

    // Другие методы, общие для всех персонажей
};