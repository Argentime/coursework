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

void Character::setName(string name) {
    this->name = name;
}

void Character::setHealth(int hp, float def, int maxHp) {
    this->hp.health = (hp ==-1) ? this->hp.health : hp;
    this->hp.defense = (def == -1) ? this->hp.defense : def;
    this->hp.maxHealth = (maxHp == -1) ? this->hp.maxHealth : maxHp;
}

void Character::setFocus(int focus) {
    this->focus = focus;
}


Character::Character(string name, int health, int foc) : name(name), focus(foc) {
	hp.maxHealth = health;
	hp.health = health;
    hp.defense = 1;
};

Character::Character(string name, HealthStats health, int foc) : name(name), focus(foc), hp(health) {};

Character::~Character() = default;

ostream& operator<<(ostream& os, const Character& character) {
    os << "Имя: " << character.name << endl;
    os << "Состояние: " << character.status() << endl;
    os << "Сосредоточенность: " << character.focus << endl;
    return os;
}

bool operator==(HealthStats hp, int percent) {
    int healthPercentage = (hp.health * 100) / hp.maxHealth;
    return healthPercentage <= percent;
}

string Character::status() const {
    //Stat Stats;

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
