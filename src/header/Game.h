#pragma once
#include "functions.h"
#include "SecondWindow.h"
#include "StoryManager.h"
#include "EventSystem.h"

class SecondWindow;

class Game
{
private:
    SecondWindow* gameWindow;
    std::unique_ptr<Hero> hero;           // Главный герой
    Enemy *enemies;           // Список врагов
    int enemyCount;
    Battle *currentBattle; // Текущее сражение
    enum class GameState { MainMenu, InGame, InBattle, Settings, Exit };
    GameState currentState;
    bool isBookPickUp = false;
    bool spellChoose = false;
    StoryManager storyManager;
    EventSystem eventSystem;

public:
    Game(SecondWindow* window);

    void start();                          // Запустить игру
    void mainMenu();                       // Главное меню
    void startNewGame();                   // Начать новую игру
    void loadGame(const std::string& saveFile); // Загрузить сохранение
    void saveGame(const std::string& saveFile); // Сохранить игру
    void update();                         // Основной цикл обновления
    void startBattle(Enemy& enemy);        // Начать сражение
    void exitGame();
};

