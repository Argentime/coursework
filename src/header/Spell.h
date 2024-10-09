#pragma once
#include "header/functions.h"

class Spell {
public:
    std::string name;
    Element element1;
    Element element2;
    int damage;
    int uses=0;

    Spell(std::string const& n, Element el1, Element el2, int dmg);

    Spell(const Spell& other);

    Spell& operator=(const Spell& other);

    friend std::ostream& operator<<(std::ostream& os, const Spell& spell) {
        os << spell.name
            << ": " << elementToString(spell.element1)
            << " + " << elementToString(spell.element2)
            << ", Урон: " << spell.damage << std::endl;
        return os;
    };

    void useSpell();

private:
    
    void evolve();
};