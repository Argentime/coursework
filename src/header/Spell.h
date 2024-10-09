#pragma once
#include "header/functions.h"

class Spell {
public:
    std::string name;
    Element element1;
    Element element2;
    int damage;
    int uses;

    Spell(std::string const& n, Element el1, Element el2, int dmg);

    Spell(const Spell& other);

    Spell& operator=(const Spell& other);

    friend std::ostream& operator<<(std::ostream& os, const Spell& spell);

    void useSpell();

private:
    
    void evolve();

};