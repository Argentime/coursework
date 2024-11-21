#pragma once
#include "Hero.h"
#include "Enemy.h"

class Battle {
private:
    Hero& hero;
    Enemy& enemy;
    bool battleFinished;

public:
    Battle(Hero& h, Enemy& e);

    void processBattle(); // Обработка битвы
    bool isBattleFinished() const;
};