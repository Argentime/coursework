#include "header/functions.h"

Game::Game(SecondWindow* window)
    : hero(std::make_unique<Hero>("Игрок", 100, 50, 100)),
    currentState(GameState::MainMenu), enemies(nullptr), enemyCount(0),
    gameWindow(window), currentBattle(nullptr)
{}

void Game::start() {
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
                //currentBattle.reset(); // Завершить сражение
                currentState = GameState::InGame;
            }
        }
        break;
    case GameState::Settings:
        currentState = GameState::MainMenu;
        break;
    case GameState::Exit:
        break;
    }
}

void Game::mainMenu() {
    
}

void Game::startNewGame() {
    hero = std::make_unique<Hero>("Игрок", 100, 50, 1000);
    enemyCount = 2;
        enemies[0] = new Enemy("Волк", 50, 20);
        enemies[1] = new Enemy("Босс", 200, 50);
    currentState = GameState::InGame;
    std::cout << "New game is started!\n";
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
    
}

void Game::startBattle(Enemy& enemy) {
    
}

void Game::exitGame() {
    currentState = GameState::Exit;
}