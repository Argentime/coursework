#include "header/Hero.h"
#include "header/functions.h"
#include "header/Warrior.h"
#include <random>

using namespace std;

Hero::Hero(string const& name, int health, int focus, int money)
    : Character(name, health, focus), money(money) {
    mana = new int[static_cast<int>(Element::Spirit) + 1];
    for (int i = 0; i < 5; ++i) {
        mana[i] = 100;
    }
}

Hero::Hero(string const& name, HealthStats newHealth, int focus, int money, int *mana)
    : Character(name, newHealth, focus), money(money), mana(mana) {}

Hero::Hero(const Hero& other)
    : Character(other.getName(), other.getHealth(), other.getFocus()),
    money(other.getMoney()),
    mySpellBook(other.getSpellBook()),
    mana(new int[static_cast<int>(Element::Spirit)+1])
{
    for (int i = 0; i <= static_cast<int>(Element::Spirit); i++) {
        mana[i] = other.getMana(Element(i));
    }
}

Hero::~Hero() {
    delete[] mana;
}

Hero& Hero::operator=(const Hero& another) {
    name = another.getName();
    hp = another.getHealth();
    focus = another.getFocus();
    money = another.getMoney();
    for (int i = 0; i <= static_cast<int>(Element::Spirit); i++) {
        mana[i] = another.getMana(Element(i));
    }
    mySpellBook = another.getSpellBook();
    return *this;
}

ostream& operator<<(ostream& os, const Hero& hero) {
    using enum Element;
    const Character* characterPtr = &hero;
    
    os << "Имя: " << hero.getName() << endl;
    os << "Состояние: " << characterPtr->status() << endl;
    os << "Сосредоточенность: " << hero.getFocus() << endl;
    os << "Мана: " << endl;
    os << "Огонь: " << hero.getMana(Fire) << endl;
    os << "Земля: " << hero.getMana(Earth) << endl;
    os << "Вода: " << hero.getMana(Water) << endl;
    os << "Воздух: " << hero.getMana(Air) << endl;
    os << "Дух: " << hero.getMana(Spirit) << endl;
    return os;
}

int Hero::getMoney() const {
    return money;
}

void Hero::setMoney(int newMoney) {
    money = newMoney;
}

int Hero::getMana(Element el) const {
    using enum Element;
    switch (el) {
    
    case Fire: return mana[0];
    case Earth: return mana[1];
    case Water: return mana[2];
    case Air: return mana[3];
    case Spirit: return mana[4];
    default: return 0;
    }
}

void Hero::setMana(int element, int value) {
    if (element >= 0 && element < 5) {
        mana[element] = value;
    }
}

const SpellBook& Hero::getSpellBook() const {
    return mySpellBook;
}

SpellBook& Hero::getSpellBook() {
    return mySpellBook;
}

std::string Hero::status() const {
    if (hp == Stats.VeryWeak) {
        return "Вы присмерти";
    }
    else if (hp == Stats.Weak) {
        return "Вы еле стоите на ногах";
    }
    else if (hp == Stats.Normal) {
        return "Вас немного шатает";
    }
    else if (hp == Stats.Strong) {
        return "Вы чувствуете себя неплохо";
    }
    else {
        return "Вы полны сил!";
    }
}

void Hero::attack(Hero& another, Spell& spell) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0,100);

    bool hitChance = (another.getFocus()) > (distrib(gen));
    another.takeDamage(((spell.damage)*hitChance));
    decreaseFocus((spell.damage*0.5));
    another.decreaseFocus(spell.damage * 1.2);
} 

void Hero::disperseFocus(Hero& another, int impact) {
    another.decreaseFocus(impact);
}
