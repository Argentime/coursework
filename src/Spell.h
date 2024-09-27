#pragma once
#include "functions.h"

using namespace std;

class Spell {
public:
    string name;
    Element element1;
    Element element2;
    int damage;
    int uses;

    Spell(string const& n, Element el1, Element el2, int dmg);

    void display() const;

    void useSpell();

private:
    void evolve();
};