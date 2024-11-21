#include "header/Game.h"
#include <iostream>

Game::Game()
    : hero(std::make_unique<Hero>("Игрок", 100, 50, 1000)),
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
                    currentBattle.reset(); // Завершить сражение
                    currentState = GameState::InGame;
                }
            }
            break;
        case GameState::Settings:
            std::cout << "Настройки игры (реализация в будущем)\n";
            currentState = GameState::MainMenu;
            break;
        case GameState::Exit:
            break;
        }
    }
}

void Game::mainMenu() {
    int choice;
    std::cout << "Главное меню:\n"
        << "1. Начать новую игру\n"
        << "2. Загрузить игру\n"
        << "3. Настройки\n"
        << "4. Выход\n"
        << "Выбор: ";
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
        std::cout << "Неверный выбор\n";
    }
}

void Game::startNewGame() {
    hero = std::make_unique<Hero>("Игрок", 100, 50, 1000);
    enemies = { Enemy("Волк", 50, 20), Enemy("Босс", 200, 50) };
    currentState = GameState::InGame;
    std::cout << "Новая игра началась!\n";
}

void Game::loadGame(const std::string& saveFile) {
    try {
        // Логика загрузки сохранения (добавить позже)
        std::cout << "Игра загружена из " << saveFile << "\n";
        currentState = GameState::InGame;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка загрузки игры: " << e.what() << "\n";
        mainMenu();
    }
}

void Game::saveGame(const std::string& saveFile) {
    try {
        // Логика сохранения игры (добавить позже)
        std::cout << "Игра сохранена в " << saveFile << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка сохранения игры: " << e.what() << "\n";
    }
}

void Game::update() {
    /*std::cout << "Вы путешествуете по миру...\n";
    if (!enemies.empty()) {
        std::cout << "На вашем пути враг: " << enemies.back().getName() << "\n";
        startBattle(enemies.back());
        enemies.pop_back();
    }
    else {
        std::cout << "Все враги побеждены! Вы выиграли игру!\n";
        currentState = GameState::MainMenu;
    }*/
}

void Game::startBattle(Enemy& enemy) {
    /*std::cout << "Началось сражение с " << enemy.getName() << "!\n";
    currentBattle = std::make_unique<Battle>(*hero, enemy);
    currentState = GameState::InBattle;*/
}

void Game::exitGame() {
    //std::cout << "Выход из игры...\n";
    currentState = GameState::Exit;
}