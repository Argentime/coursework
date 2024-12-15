#pragma once

#include "functions.h"

enum class SpellType {
    Attack,
    Defense,
    Heal,
	Focus
};

class Spell {
public:
    std::string name;
    Element element1;
    Element element2;
    int damage;
    int uses = 0;
    SpellType type;

    Spell(std::string const& n, Element el1, Element el2, int value, SpellType type);
    Spell(const Spell& other);
    Spell& operator=(const Spell& other);


    void applyDefenseBuff(Hero& hero);
    void restore(Hero& hero, int amount, bool restoreFocus);
    void useSpell();
    void evolve();

    virtual ~Spell() = default;
};
