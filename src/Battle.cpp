#include "header/Battle.h"
#include "header/functions.h"
#include "header/Game.h" 
#include "header/SecondWindow.h" 
#include <random>
#include <QDebug>
#include <QPushButton>
#include <QWidget>


Battle::Battle(Hero& hero, Enemy& enemy, Game* game, SecondWindow* window) : hero(hero),enemy(enemy), game(game), window(window), isHeroTurn(true) {}

void Battle::processBattle() {
    switch (enemy.getHealth().maxHealth) {
    case 50:
        loadHtmlToLabel(window->ui.label, "resources/quest_html/wolves_battle.html");
        break;
    case 100:
        loadHtmlToLabel(window->ui.label, "resources/quest_html/ghost_battle.html");
        break;
    case 200:
        loadHtmlToLabel(window->ui.label, "resources/quest_html/deathbringer_battle.html");
        break;
    }
    updateButtons();
}


void Battle::updateButtons() {
    std::vector<std::pair<QString, std::function<void()>>> actions;

    if (isHeroTurn) {
        actions.push_back({ "Оценить врага", [this]() { this->evaluateEnemy(); } });
        actions.push_back({ "Книга заклинаний", [this]() { this->showSpellBook(); } });
        actions.push_back({ "Бежать", [this]() { this->runAway(); } });

    }
    else {
        actions.push_back({ "Далее", [this]() { this->nextTurn(); } });


    }

    window->updateButtons(actions);
}

void Battle::nextTurn() {

    isHeroTurn = true; 
    updateButtons(); 

    if (hero.getHealth().health <= 0)
    {
        window->ui.label->setText(QString("%1 потерпел поражение в битве!").arg(QString::fromStdString(hero.getName())));
        return;

    }

    if (enemy.getHealth().health <= 0)
    {
        window->ui.label->setText(QString("%1 победил в битве!").arg(QString::fromStdString(hero.getName())));
        game->storyManager.completeCurrentStage();
        game->storyManager.startNextStage();
        return;

    }



}

void Battle::heroTurn() {
    window->ui.label->setText("Ваш ход.\n");
    isHeroTurn = true;
    updateButtons();
}

void Battle::castSpell(Spell* spell) {
    window->ui.label->setText(QString("%1 применяет %2").arg(QString::fromStdString(hero.getName()), QString::fromStdString(spell->name)));
    hero.attack(enemy, *spell);
    spell->useSpell();
    if (hero.getMana(spell->element1) >= 0 && hero.getMana(spell->element2) >= 0) {
        hero.setMana(static_cast<int>(spell->element1), hero.getMana(spell->element1) - 10);
        hero.setMana(static_cast<int>(spell->element2), hero.getMana(spell->element2) - 10);
    }
    else {
        hero.setMana(static_cast<int>(spell->element1), 0);
        hero.setMana(static_cast<int>(spell->element2), 0);
    }
    isHeroTurn = false;
    enemyTurn();
}

void Battle::enemyTurn() {

    window->ui.label->setText("Ход противника.\n");



    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, enemy.getSpellBook().getSpellCount() - 1);


    if (enemy.getSpellBook().getSpellCount() > 0)
    {
        auto* spell = enemy.getSpellBook().getSpells()[distrib(gen)];
        int damage = spell->damage;
        hero.takeDamage(damage);
        window->ui.label->setText(QString("%1 применяет %2. %3 получает %4 урона.").arg(QString::fromStdString(enemy.getName()), QString::fromStdString(spell->name), QString::fromStdString(hero.getName()), QString::number(damage)));
    }
    else {
        int damage = 15;
        hero.takeDamage(damage);
        window->ui.label->setText(QString("%1 атакует. %2 получает %3 урона.").arg(QString::fromStdString(enemy.getName()), QString::fromStdString(hero.getName()), QString::number(damage)));
    }

    updateButtons();
}


void Battle::evaluateEnemy()
{
    window->ui.label->setText(QString("Здоровье %1: %2").arg(QString::fromStdString(enemy.getName()), QString::number(enemy.getHealth().health)));

}

void Battle::showSpellBook()
{
    std::vector<std::pair<QString, std::function<void()>>> actions;
    QString ss = "<html><body>";
    ss += "<p><b>Ваши заклинания:</b></p>";


    const SpellBook& spellBook = hero.getSpellBook();
    for (int i = 0; i < spellBook.getSpellCount(); ++i) {
        Spell* spell = spellBook.getSpells()[i];

        ss += "<br>";
        ss += "<span style=\"color: #0078D7; font-weight: bold;\">" + QString::fromStdString(spell->name).toHtmlEscaped() + ": </span>";
        ss += "Стихии: <span style=\"color: #FF5733;\">" + QString::fromStdString(elementToString(spell->element1)).toHtmlEscaped() + " </span>";
        if (spell->element2 != Element::None) {
            ss += " + <span style=\"color: #FF5733;\">" + QString::fromStdString(elementToString(spell->element2)).toHtmlEscaped() + " </span>";
        }
        ss += "Урон: <span style=\"color: #DC143C; font-weight: bold;\">" + QString::number(spell->damage) + " </span>";
        ss += "Использований: " + QString::number(spell->uses);
        ss += "</br>";
    }

    ss += "</body></html>";

    window->ui.label->setText(ss);
    for (int i = 0; i < hero.getSpellBook().getSpellCount(); ++i) {
        Spell* spell = hero.getSpellBook().getSpells()[i];
        actions.push_back({ QString::fromStdString(spell->name), [this, spell]() { this->castSpell(spell); } });
    }

    window->updateButtons(actions);
}


void Battle::runAway() {
    window->ui.label->setText("Вы сбежали с поля боя.");
    game->storyManager.restartStage("Хижина Путника");
}