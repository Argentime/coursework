#pragma once
class Hero;

class Warrior {
public:
    virtual void attack(Hero& another, int damage) = 0;
    virtual void disperseFocus(Hero& another, int impact) = 0;
    virtual ~Warrior() = default;
};