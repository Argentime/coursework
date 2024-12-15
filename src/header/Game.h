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
    Enemy *enemies;
    int enemyCount;
    bool isAmuletFounded = false;
    bool isBarierDestroyed = false;
    friend class Battle;
    Battle *currentBattle;
    enum class GameState { MainMenu, InGame, InBattle, Settings, Exit };
    GameState currentState;
    bool isBookPickUp = false;
    bool spellChoose = false;
    
    EventSystem eventSystem;
    void showMerchantOptions();
    void processPurchase(const QString& item, int cost, int itemType);
    void displayBattle(const QString& enemy);
    void useAltarOfPower();
    void initializeEnemies();
    void displayWorldMap();

public:
    Game(SecondWindow* window);
    std::unique_ptr<Hero> hero;
    StoryManager storyManager;
    void start();
    void startNewGame();
    void loadGame(const std::string& saveFile);
    void saveGame(const std::string& saveFile);
    void startBattle(Enemy& enemy);
    void exitGame();
};

