#pragma once
#include "header/functions.h"

const struct Stat {
    int VeryWeak = 20;
    int Weak = 40;
    int Normal = 60;
    int Strong = 80;
}Stats;

class Character {
protected:
    std::string name;
    HealthStats hp;
    int focus;

public:

    std::string getName() const;

	int getFocus() const;

	HealthStats getHealth() const;

    void setName(std::string name);

    void setFocus(int focus);

    void setHealth(int hp, float def, int maxHp);


    Character(std::string name, int health, int focus);

    Character(std::string name, HealthStats health, int foc);

    ~Character();

    friend std::ostream& operator<<(std::ostream& os, const Character& c);

    std::string status() const;

    void takeDamage(int dmg);

    void restoreHealth(int amt);

    void restoreFocus(int amt);

    void decreaseFocus(int amt);
};