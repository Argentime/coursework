#pragma once
#include "Spell.h"

class SpellBook {
private:
    Spell** spells;
    int spellCount;

public:

    ~SpellBook();

        void addSpell(std::string const& name, Element el1, Element el2, int damage);

        void displaySpells() const;

        void updateSpell(std::string_view oldName, std::string_view newName, int newDamage) const;

        void removeSpell(std::string const& name);

        Spell* findSpellByName(std::string_view name) const;

        void castSpell(std::string_view name) const;

}; //awd