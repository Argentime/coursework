#pragma once
class Hero;
class Spell;

class Warrior {
public:
    virtual void attack(Hero& another, int damage) = 0;
    virtual void disperseFocus(Hero& another, Spell& spell) = 0;
    virtual ~Warrior() = default;
};