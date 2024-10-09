#include "header/functions.h"

using namespace std;
  
string Character::getName() const {
    return name;
}

HealthStats Character::getHealth() const {
    return hp;
}

int Character::getFocus() const {
    return focus;
}

void Character::setName(string_view const& newName) {
    this->name = newName;
}

void Character::setHealth(int health, float def, int maxHp) {
    this->hp.health = (hp ==-1) ? this->hp.health : health;
    this->hp.defense = (def == -1) ? this->hp.defense : def;
    this->hp.maxHealth = (maxHp == -1) ? this->hp.maxHealth : maxHp;
}

void Character::setFocus(int foc) {
    this->focus = foc;
}


Character::Character(string const& newName, int health, int foc) : name(newName), focus(foc) {
	hp.maxHealth = health;
	hp.health = health;
    hp.defense = 1;
};

Character::Character(string const& newName, HealthStats health, int foc) : name(newName), hp(health), focus(foc) {};

Character::~Character() = default;

ostream& operator<<(ostream& os, const Character& character) {
    os << "Имя: " << character.name << endl;
    os << "Состояние: " << character.status() << endl;
    os << "Сосредоточенность: " << character.focus << endl;
    return os;
}



string Character::status() const {
    Stat Stats;

    if (hp == Stats.VeryWeak) {
        return "Присмерти";
    }
    else if (hp == Stats.Weak) {
        return "Еле стоите на ногах";
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

void Character::takeDamage(int dmg) {
    hp.health = (hp.health - dmg * hp.defense > 0) ? hp.health - dmg * hp.defense : 0;
}

void Character::restoreHealth(int amt) {
    hp.health = (hp.health + amt > hp.maxHealth) ? hp.maxHealth : hp.health + amt;
}

void Character::restoreFocus(int amt) {
    focus = (focus + amt > 100) ? 100 : focus + amt;
}

void Character::decreaseFocus(int amt) {
    focus = (focus - amt < 0) ? 0 : focus - amt;
}
