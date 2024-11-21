#pragma once
#include "functions.h"

class Game
{
private:
    std::unique_ptr<Hero> hero;           // Главный герой
    Enemy *enemies;           // Список врагов
    int enemyCount;
    Battle *currentBattle; // Текущее сражение
    enum class GameState { MainMenu, InGame, InBattle, Settings, Exit };
    GameState currentState;

public:
    Game();

    void start();                          // Запустить игру
    void mainMenu();                       // Главное меню
    void startNewGame();                   // Начать новую игру
    void loadGame(const std::string& saveFile); // Загрузить сохранение
    void saveGame(const std::string& saveFile); // Сохранить игру
    void update();                         // Основной цикл обновления
    void startBattle(Enemy& enemy);        // Начать сражение
    void exitGame();
};

