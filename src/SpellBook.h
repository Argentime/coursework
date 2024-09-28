#pragma once
#include "Spell.h"

using namespace std;

class SpellBook {
private:
    
    Spell** spells;
    int spellCount;

public:

    SpellBook();

    SpellBook(Spell** initialSpells, int count);

    ~SpellBook();

    void addSpell(string const& name, Element el1, Element el2, int damage);

    void displaySpells() const;

    void updateSpell(string_view oldName, string_view newName, int newDamage) const;

    void removeSpell(string const& name);

    Spell* findSpellByName(string_view name) const;

    void castSpell(string_view name) const;

};