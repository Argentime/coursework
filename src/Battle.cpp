#include "header/Battle.h"
#include <iostream>

Battle::Battle(Hero& h, Enemy& e) : hero(h), enemy(e), battleFinished(false) {}

void Battle::processBattle() {
    //while (hero.getHealth() > 0 && enemy.getHealth() > 0) {
    //    // ����� �����
    //    hero.attack(enemy);
    //    if (enemy.getHealth() <= 0) {
    //        std::cout << "�� �������� �����!\n";
    //        battleFinished = true;
    //        return;
    //    }

    //    // ����� �����
    //    enemy.attack(hero);
    //    if (hero.getHealth() <= 0) {
    //        std::cout << "�� ��������� �����!\n";
    //        battleFinished = true;
    //        return;
    //    }
    //}
}

bool Battle::isBattleFinished() const {
    return battleFinished;
}