#pragma once
#include "functions.h"

class Spell {
public:
    std::string name;
    Element element1;
    Element element2;
    int damage;
    int uses;

    Spell(std::string const& n, Element el1, Element el2, int dmg);

    void display() const;

    void useSpell();

private:
    
    void evolve();

};