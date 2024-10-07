#pragma once
#include "Spell.h"

class SpellBook {
private:   

    

public:

    Spell** spells;

    int spellCount;

    Spell** getSpells() const;

	int getSpellCount() const;


    SpellBook();

    SpellBook(const SpellBook& another);

	SpellBook& operator=(const SpellBook& another);

    ~SpellBook();

    void addSpell(std::string const& name, Element el1, Element el2, int damage);

    void displaySpells() const;

    void updateSpell(std::string_view oldName, std::string_view newName, int newDamage) const;

    void removeSpell(std::string const& name);

    Spell* findSpellByName(std::string_view name) const;

    void castSpell(std::string_view name) const;

};