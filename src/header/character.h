#pragma once
#include "functions.h"

class Character {
protected:
    std::string name;
    HealthStats hp;
    int focus;

public:

    std::string getName() const;

	int getFocus() const;

	HealthStats getHealth() const;


    Character(std::string name, int health, int focus);

    ~Character();

    friend std::ostream& operator<<(std::ostream& os, const Character& c);

    void takeDamage(int dmg);

    void restoreHealth(int amt);

    void restoreFocus(int amt);

    void decreaseFocus(int amt);
};