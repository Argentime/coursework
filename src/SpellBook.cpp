#include "header/functions.h"

using namespace std;

Spell** SpellBook::getSpells() const {
    return spells;
}

int SpellBook::getSpellCount() const {
	return spellCount;
}


SpellBook::SpellBook() : spells(nullptr), spellCount(0) {};

SpellBook::SpellBook(const SpellBook& another) : spellCount(another.spellCount) {
    spells = new Spell * [spellCount];
    for (int i = 0; i < spellCount; ++i) {
        spells[i] = new Spell(*another.spells[i]); 
    }
}

SpellBook& SpellBook::operator=(const SpellBook& another) = default;

ostream& operator<<(ostream& os, const SpellBook& mySpellBook);

SpellBook::~SpellBook() {
    for (int i = 0; i < spellCount; ++i) {
        delete spells[i];
    }
    delete[] spells;
}

void SpellBook::addSpell(string const& name, Element el1, Element el2, int damage) {
    auto newSpells = new Spell * [spellCount + 1];
    for (int i = 0; i < spellCount; ++i) {
        newSpells[i] = spells[i];
    }
    newSpells[spellCount] = new Spell(name, el1, el2, damage);
    delete[] spells;
    spells = newSpells;
    spellCount++;
}

void SpellBook::updateSpell(string_view oldName, string_view newName, int newDamage) const {
    Spell* spellToUpdate = findSpellByName(oldName);

    if (spellToUpdate == nullptr) {
        cout << "Заклинание с таким именем не найдено.\n";
        return;
    }
    spellToUpdate->name = newName;
    spellToUpdate->damage = newDamage;
    cout << "Заклинание обновлено.\n";
}

void SpellBook::removeSpell(string const& name) {
    const Spell* spellToRemove = findSpellByName(name);
    if (spellToRemove == nullptr) {
        cout << "Заклинание с таким именем не найдено.\n";
        return;
    }

    for (int i = 0; i < spellCount; ++i) {
        if (spells[i] == spellToRemove) {
            delete spells[i];
            for (int j = i; j < spellCount - 1; ++j) {
                spells[j] = spells[j + 1];
            }
            spellCount--;
            spells[spellCount] = nullptr;
            cout << "Заклинание удалено.\n";
            return;
        }
    }
}

Spell* SpellBook::findSpellByName(string_view name) const {
    for (int i = 0; i < spellCount; ++i) {
        if (spells[i]->name == name) {
            return spells[i];
        }
    }
    return nullptr;
}

void SpellBook::castSpell(string_view name) const {
    Spell* spellToCast = findSpellByName(name);
    if (spellToCast == nullptr) {
        cout << "Данного заклинания не найденно\n";
        return;
    }
    spellToCast->useSpell();
}