#include "header/Game.h"
#include <iostream>

Game::Game()
    : hero(std::make_unique<Hero>("�����", 100, 50, 1000)),
    currentState(GameState::MainMenu) 
{
    for (int i = 0; i < enemyCount; ++i) {
        enemies[i] = new Enemy("",0,0);
    }
}

void Game::start() {
    while (currentState != GameState::Exit) {
        switch (currentState) {
        case GameState::MainMenu:
            mainMenu();
            break;
        case GameState::InGame:
            update();
            break;
        case GameState::InBattle:
            if (currentBattle) {
                currentBattle->processBattle();
                if (currentBattle->isBattleFinished()) {
                    currentBattle.reset(); // ��������� ��������
                    currentState = GameState::InGame;
                }
            }
            break;
        case GameState::Settings:
            std::cout << "��������� ���� (���������� � �������)\n";
            currentState = GameState::MainMenu;
            break;
        case GameState::Exit:
            break;
        }
    }
}

void Game::mainMenu() {
    int choice;
    std::cout << "������� ����:\n"
        << "1. ������ ����� ����\n"
        << "2. ��������� ����\n"
        << "3. ���������\n"
        << "4. �����\n"
        << "�����: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        startNewGame();
        break;
    case 2:
        loadGame("save.dat");
        break;
    case 3:
        currentState = GameState::Settings;
        break;
    case 4:
        exitGame();
        break;
    default:
        std::cout << "�������� �����\n";
    }
}

void Game::startNewGame() {
    hero = std::make_unique<Hero>("�����", 100, 50, 1000);
    enemies = { Enemy("����", 50, 20), Enemy("����", 200, 50) };
    currentState = GameState::InGame;
    std::cout << "����� ���� ��������!\n";
}

void Game::loadGame(const std::string& saveFile) {
    try {
        // ������ �������� ���������� (�������� �����)
        std::cout << "���� ��������� �� " << saveFile << "\n";
        currentState = GameState::InGame;
    }
    catch (const std::exception& e) {
        std::cerr << "������ �������� ����: " << e.what() << "\n";
        mainMenu();
    }
}

void Game::saveGame(const std::string& saveFile) {
    try {
        // ������ ���������� ���� (�������� �����)
        std::cout << "���� ��������� � " << saveFile << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "������ ���������� ����: " << e.what() << "\n";
    }
}

void Game::update() {
    /*std::cout << "�� ������������� �� ����...\n";
    if (!enemies.empty()) {
        std::cout << "�� ����� ���� ����: " << enemies.back().getName() << "\n";
        startBattle(enemies.back());
        enemies.pop_back();
    }
    else {
        std::cout << "��� ����� ���������! �� �������� ����!\n";
        currentState = GameState::MainMenu;
    }*/
}

void Game::startBattle(Enemy& enemy) {
    /*std::cout << "�������� �������� � " << enemy.getName() << "!\n";
    currentBattle = std::make_unique<Battle>(*hero, enemy);
    currentState = GameState::InBattle;*/
}

void Game::exitGame() {
    //std::cout << "����� �� ����...\n";
    currentState = GameState::Exit;
}