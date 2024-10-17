#pragma once
class Hero;
class Spell;

class Warrior {
public:
    virtual void attack(Hero& another, Spell& spell) = 0;
    virtual void disperseFocus(Hero& another, int impact) = 0;
    virtual ~Warrior() = default;
};