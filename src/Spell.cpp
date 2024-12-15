#include "header/Spell.h"
#include "header/functions.h"
#include "header/Hero.h"
#include <iostream>


using namespace std;

Spell::Spell(std::string const& n, Element el1, Element el2, int value, SpellType type)
    : name(n), element1(el1), element2(el2), damage(value), type(type) {}

Spell& Spell::operator=(const Spell& other) {
    if (this != &other) {
        name = other.name;
        element1 = other.element1;
        element2 = other.element2;
        damage = other.damage;
        uses = other.uses;
        type = other.type;
    }
    return *this;
}

Spell::Spell(const Spell& other) {
    if (this != &other) {
        name = other.name;
        element1 = other.element1;
        element2 = other.element2;
        damage = other.damage;
        uses = other.uses;
        type = other.type;
    }
    delete this;
}


void Spell::applyDefenseBuff(Hero& hero) {
    hero.setHealth(-1, hero.getHealth().defense *0.5, -1);
}

void Spell::restore(Hero& hero, int amount, bool restoreFocus) {
    if (restoreFocus) {
        hero.restoreFocus(amount);
    }
    else {
        hero.restoreHealth(amount);
    }
}

void Spell::useSpell() {
    uses++;
    evolve();
}

void Spell::evolve() {
    if (uses % 3 == 0) {
        damage += 5;
    }
}