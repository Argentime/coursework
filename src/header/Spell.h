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

    Spell(const Spell& other);

	Spell& operator=(const Spell& other);

    ~Spell();

    void display() const;

    void useSpell();

private:
    
    void evolve();

};