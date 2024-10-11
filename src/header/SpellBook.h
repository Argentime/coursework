#pragma once
#include "header/functions.h"

class SpellBook {
private:   

    Spell** spells;

    int spellCount;

public:

    Spell** getSpells() const;

	int getSpellCount() const;

    friend std::ostream& operator<<(std::ostream& os, const SpellBook& mySpellBook) {

        os << "Книга заклинаний:" << std::endl;

        if (mySpellBook.getSpellCount() == 0) {
            os << "Заклинаний нет. \n";
        }
        else {
            for (int i = 0; i < mySpellBook.getSpellCount(); ++i) {
                os << *mySpellBook.getSpells()[i];
            }
        }
        return os;
    }

    SpellBook();

    SpellBook(const SpellBook& another);

	SpellBook& operator=(const SpellBook& another);

    ~SpellBook();

    void addSpell(std::string const& name, Element el1, Element el2, int damage);

    void updateSpell(std::string_view oldName, std::string_view newName, int newDamage) const;

    void removeSpell(std::string const& name);

    Spell* findSpellByName(std::string_view name) const;

    void castSpell(std::string_view name) const;

};