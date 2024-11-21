#pragma once
#include "Hero.h"
#include "Enemy.h"
#include "Battle.h"

class Game
{
private:
    std::unique_ptr<Hero> hero;           // ������� �����
    Enemy *enemies;           // ������ ������
    int enemyCount;
    std::unique_ptr<Battle> currentBattle; // ������� ��������
    enum class GameState { MainMenu, InGame, InBattle, Settings, Exit };
    GameState currentState;

public:
    Game();

    void start();                          // ��������� ����
    void mainMenu();                       // ������� ����
    void startNewGame();                   // ������ ����� ����
    void loadGame(const std::string& saveFile); // ��������� ����������
    void saveGame(const std::string& saveFile); // ��������� ����
    void update();                         // �������� ���� ����������
    void startBattle(Enemy& enemy);        // ������ ��������
    void exitGame();
};

