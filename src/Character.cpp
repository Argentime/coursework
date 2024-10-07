#include "header/Character.h"

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



Character::Character(string name, int health, int foc) : name(name), focus(foc) {
	hp.maxHealth = health;
	hp.health = health;
    hp.defense = 1;
};

Character::~Character() = default;

ostream& operator<<(ostream& os, const Character& character) {
    os << "Name: " << character.name << "\n";
    os << "Health: " << character.hp.health << "/" << character.hp.maxHealth << "\n";
    os << "Focus: " << character.focus << "\n";
    return os;
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
