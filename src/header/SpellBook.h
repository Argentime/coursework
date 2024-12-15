#pragma once

#include "Spell.h"
#include <vector>
#include <iostream>

class Spell;
enum class SpellType;

class SpellBook {
private:
    std::vector<Spell*> spells;
    int spellCount = 0;

public:
    SpellBook() = default;
    SpellBook(const SpellBook& other);
    SpellBook& operator=(const SpellBook& another);
    ~SpellBook();

    Spell** getSpells() const;
    Spell* getSpell(int i) const;
    int getSpellCount() const;

    void addSpell(const std::string& name, Element el1, Element el2, int value, SpellType type);

    void addSpell(const Spell& other);

    void updateSpell(std::string_view oldName, std::string_view newName, int newDamage) const;

    void removeSpell(std::string const& name);

    Spell* findSpellByName(std::string_view name) const;

    void castSpell(std::string_view name) const;

};