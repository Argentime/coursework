#include "header/functions.h"

Battle::Battle(Hero& h, Enemy& e) : hero(h), enemy(e), battleFinished(false) {}

void Battle::processBattle() {
    //while (hero.getHealth() > 0 && enemy.getHealth() > 0) {
    //    // Атака героя
    //    hero.attack(enemy);
    //    if (enemy.getHealth() <= 0) {
    //        std::cout << "Вы победили врага!\n";
    //        battleFinished = true;
    //        return;
    //    }

    //    // Атака врага
    //    enemy.attack(hero);
    //    if (hero.getHealth() <= 0) {
    //        std::cout << "Вы проиграли битву!\n";
    //        battleFinished = true;
    //        return;
    //    }
    //}
}

bool Battle::isBattleFinished() const {
    return battleFinished;
}