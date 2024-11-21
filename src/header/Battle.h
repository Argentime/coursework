#pragma once
#include "functions.h"

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