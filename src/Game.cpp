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
        storyManager.startNextStage();
        storyManager.completeCurrentStage();
        break;
    case GameState::InBattle:
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
    eventSystem.registerEvent("FindArtifact", []() {
        std::cout << "You found the artifact! Moving to the next stage.\n";
    });

    eventSystem.registerEvent("BattleStart", [&]() {
        startBattle(enemies[0]);
    });

    // Adding story stages
    storyManager.addStage(std::make_shared<StoryStage>(
        "Chapter 1: Awakening",
        []() { std::cout << "You wake up in a strange room...\n"; },
        []() { std::cout << "You leave the room.\n"; }
    ));

    storyManager.addStage(std::make_shared<StoryStage>(
        "Chapter 2: Find the artifact",
        [&]() { eventSystem.triggerEvent("FindArtifact"); },
        []() { std::cout << "The artifact has been found.\n"; }
    ));

    storyManager.addStage(std::make_shared<StoryStage>(
        "Chapter 3: Goblin battle",
        [&]() { eventSystem.triggerEvent("BattleStart"); },
        []() { std::cout << "The goblin has been defeated.\n"; }
    ));
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
    std::cout << "Начинается битва с " << enemy.getName() << "!\n";
    Battle battle(*hero, enemy);
    battle.processBattle();

    if (hero->getHealth().health <= 0) {
        std::cout << "Вы проиграли битву. Конец игры.\n";
        exit(0);
    }
}

void Game::exitGame() {
    currentState = GameState::Exit;
}