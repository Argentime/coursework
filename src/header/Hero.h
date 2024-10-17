#pragma once
#include "functions.h"

const struct Stat {
    int VeryWeak = 20;
    int Weak = 40;
    int Normal = 60;
    int Strong = 80;
}Stats;

class Hero : public Character, public Warrior {
private:
    int money;
    SpellBook mySpellBook;
    int *mana;

public:

    Hero(std::string const& name, int health, int focus, int money);
    Hero(std::string const& name, HealthStats newHealth, int focus, int money, int* mana);
    Hero(const Hero& other);
    ~Hero() override;

    int getMoney() const;
    void setMoney(int newMoney);

    int getMana(Element element) const;
    void setMana(int element, int value);

    const SpellBook& getSpellBook() const;
    SpellBook& getSpellBook();

    Hero& operator=(const Hero& another);
    friend std::ostream& operator<<(std::ostream& os, const Hero& hero);

    std::string status() const override; 
    void attack(Hero& another, Spell& spell) override;  
    void disperseFocus(Hero& another, int impact) override;

};
