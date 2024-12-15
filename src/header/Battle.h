#pragma once

#include "Hero.h"
#include "Enemy.h"
#include "SecondWindow.h"
#include "Game.h"

class Battle {
private:
    Hero& hero;
    Enemy& enemy;

    Game* game;
    SecondWindow* window;
    bool isHeroTurn;

    void heroTurn();
    void enemyTurn();
    void updateButtons();
public:
    Battle(Hero& hero, Enemy& enemy, Game* game, SecondWindow* window);
    void processBattle();
    void nextTurn();
    void evaluateEnemy();
    void showSpellBook();
    void runAway();
    void castSpell(Spell* spell);

};