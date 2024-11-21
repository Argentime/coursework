#include "header/Enemy.h"
#include "header/functions.h"

using namespace std;


Enemy::Enemy(string const& name, int health, int focus)
    : Character(name, health, focus) {
    mana = new int[static_cast<int>(Element::Spirit) + 1];
    for (int i = 0; i < 5; ++i) {
        mana[i] = 100;
    }
}
Enemy::Enemy(const Enemy& other)
    : Character(other.getName(), other.getHealth(), other.getFocus()),
    mySpellBook(other.getSpellBook()),
    mana(new int[static_cast<int>(Element::Spirit) + 1])
{
    for (int i = 0; i <= static_cast<int>(Element::Spirit); i++) {
        mana[i] = other.getMana(Element(i));
    }
}
Enemy::~Enemy() {
    delete[] mana;
}
string Enemy::status() const {
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

void Enemy::setMana(int element, int value) {
    if (element >= 0 && element < 5) {
        mana[element] = value;
    }
}
const SpellBook& Enemy::getSpellBook() const {
    return mySpellBook;
}
SpellBook& Enemy::getSpellBook() {
    return mySpellBook;
}
int Enemy::getMana(Element el) const {
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