#include "header/functions.h"

Battle::Battle(Hero& h, Enemy& e) : hero(h), enemy(e), battleFinished(false) {}

void Battle::processBattle() {
    
}

bool Battle::isBattleFinished() const {
    return battleFinished;
}