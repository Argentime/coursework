#include "header/functions.h"

using namespace std;

Spell** SpellBook::getSpells() const {
    Spell** spellsArray = new Spell * [spellCount];
    for (int i = 0; i < spellCount; ++i) {
        spellsArray[i] = spells[i];
    }
    return spellsArray;
}

Spell* SpellBook::getSpell(int i) const {
    if (i >= 0 && i < spellCount)
    {
        return spells[i];
    }
    return nullptr;
}

int SpellBook::getSpellCount() const {
    return spellCount;
}


SpellBook::SpellBook(const SpellBook& other) : spellCount(other.spellCount)
{
    spells.reserve(spellCount);
    for (int i = 0; i < spellCount; ++i)
    {
        spells.push_back(new Spell(*other.spells[i]));
    }
}


SpellBook& SpellBook::operator=(const SpellBook& another)
{

    for (int i = 0; i < spellCount; ++i)
    {
        delete spells[i];
    }
    spells.clear();


    spellCount = another.spellCount;
    spells.reserve(spellCount);
    for (int i = 0; i < spellCount; ++i) {
        spells.push_back(new Spell(*another.spells[i]));
    }
    return *this;
}



SpellBook::~SpellBook() {
    for (int i = 0; i < spellCount; ++i) {
        delete spells[i];
    }
}

void SpellBook::addSpell(const std::string& name, Element el1, Element el2, int value, SpellType type) {

    spells.push_back(new Spell(name, el1, el2, value, type));
    spellCount++;
}
void SpellBook::addSpell(const Spell& other) {

    spells.push_back(new Spell(other));
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