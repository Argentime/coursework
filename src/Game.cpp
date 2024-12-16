#include "header/functions.h"

Game::Game(SecondWindow* window)
    : hero(std::make_unique<Hero>("Игрок", 100, 50, 100)),
     enemies(nullptr), enemyCount(0),
    gameWindow(window), currentBattle(nullptr)
{}

void Game::start() {
    storyManager.startStage(0);
}

void Game::startNewGame() {
    hero = std::make_unique<Hero>("Игрок", 100, 100, 1000);
    loadHeroSpellBookFromJson("resources/DefaultSave.json", &(hero.get()->getSpellBook()));
    initializeEnemies();

    storyManager.addStage(std::make_shared<StoryStage>(
        "Хижина Путника",
        [this]() {
            loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/lobby.html");
            gameWindow->setImage(":/rec/resources/background_images/Moi_18.png");
            gameWindow->updateButtons({
                {"Посетить торговца талисманами", [this]() { 
                    showMerchantOptions();
                    loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/merchant.html");
                    gameWindow->setImage(":/rec/resources/background_images/Park_03.png");
                }},
                {"Открыть карту мира", [this]() {
                    displayWorldMap();
                    loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/map.html");
                    gameWindow->setImage(":/rec/resources/background_images/van_45_fix.png");
                }},
                {"Использовать алтарь силы", [this]() {
                    gameWindow->updateButtons({
                    {"Воспользоваться Алтарем (-1000)", [this]() { useAltarOfPower(); }},
                    {"Вернуться", [this]() { storyManager.restartStage("Хижина Путника"); }}
                    }); 
                    loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/altar.html");
                    gameWindow->setImage(":/rec/resources/background_images/Moi_05.png");
                }}
                });
        },
        []() {
            qDebug() << "Выход из хижины.";
        }
    ));

    storyManager.addStage(std::make_shared<StoryStage>(
        "Лесной Перекресток",
        [this]() {
            loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/forest_crossroad.html");
            gameWindow->setImage(":/rec/resources/background_images/Moi_01.png");
            gameWindow->updateButtons({
                {"Сразиться с бродячими волками", [this]() { 
                    initializeEnemies();
                    startBattle(enemies[0]); 
                }},
                {"Вернуться в хижину", [this]() { storyManager.restartStage("Хижина Путника"); }}
                });
        },
        [this]() {
            qDebug() << "Вы покидаете Лесной Перекресток.";
        }
    ));

    storyManager.addStage(std::make_shared<StoryStage>(
        "Тёмный Лес",
        [this]() {
            loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/dark_forest.html");
            gameWindow->setImage(":/rec/resources/background_images/Borzukhan_01.png");
            gameWindow->updateButtons({
                {"Искать сокровища", [this]() { 
                    loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/found_amulet.html");
                    isAmuletFounded = true; 
                    }},
                {"Вернуться на Лесной Перекресток", [this]() { storyManager.restartStage("Лесной Перекресток"); }}
                });
        },
        []() {
            qDebug() << "Вы покидаете Тёмный Лес.";
        }
    ));

    storyManager.addStage(std::make_shared<StoryStage>(
        "Пещера Призраков",
        [this]() {
            loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/ghost_cave.html");
            gameWindow->setImage(":/rec/resources/background_images/Moi_03.png");
            gameWindow->updateButtons({
                {"Сразиться с Призрачным Стражем", [this]() { initializeEnemies(); startBattle(enemies[1]); }},
                {"Вернуться в хижину", [this]() { storyManager.restartStage("Хижина Путника"); }}
                });
        },
        [this]() {
            loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/ghost_cave_complete.html");
            isBarierDestroyed = true;
        }
    ));

    storyManager.addStage(std::make_shared<StoryStage>(
        "Логово Смертоносца",
        [this]() {
            if (isAmuletFounded&& isBarierDestroyed) {
                loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/boss_lair.html");
                gameWindow->setImage(":/rec/resources/background_images/Menzols_04.png");
                gameWindow->updateButtons({
                    {"Сразиться с Смертоносцем", [this]() { startBattle(enemies[2]); }},
                    {"Вернуться в хижину", [this]() { storyManager.restartStage("Хижина Путника"); }}
                    });
            }
            else {
                loadHtmlToLabel(gameWindow->ui.label, "resources/quest_html/boss_locked.html");
                gameWindow->setImage(":/rec/resources/background_images/Menzols_04.png");
                gameWindow->updateButtons({
                    {"Вернуться в хижину", [this]() { storyManager.restartStage("Хижина Путника"); }}
                    });
            }
        },
        []() {
            qDebug() << "Вы победили босса.";
        }
    ));
}

void Game::loadGame(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            qInfo() << "Ошибка: Не удалось открыть файл сохранения.";
            return;
        }

        json saveData;
        file >> saveData;
        file.close();

        
        int health = saveData["hero"]["health"];
        int maxHealth = saveData["hero"]["maxHealth"];
        float defense = saveData["hero"]["defense"];
        int focus = saveData["hero"]["focus"];
        int money = saveData["hero"]["money"];
        std::string name = saveData["hero"]["name"];

        std::vector<int> mana(5);
        for (int i = 0; i < 5; ++i) {
            mana[i] = saveData["hero"]["mana"][i];
        }

        int* manaArray = new int[5];
        for (int i = 0; i < 5; i++) manaArray[i] = mana[i];

        hero = std::make_unique<Hero>(name, HealthStats{ health, maxHealth, defense }, focus, money, manaArray);

        SpellBook& spellBook = hero->getSpellBook();
        for (const auto& spellData : saveData["hero"]["spellBook"]) {
            for (const auto& spelld : spellData.at("spells")) {
                Spell spell = deserializeSpell(spelld);
                spellBook.addSpell(spell.name, spell.element1, spell.element2, spell.damage, spell.type);
            }
        }

        storyManager.restartStage(saveData["currentStageName"]);
        isBarierDestroyed = saveData["isBarierDestroyed"];
        isAmuletFounded = saveData["isAmuletFounded"];

        qInfo() << "Игра загружена из " << QString::fromStdString(filename);

    }
    catch (const std::exception& e) {
        qInfo() << "Ошибка загрузки game: " << e.what();
    }
}

void Game::saveGame(const std::string& filename) {
    try {
        json saveData;

        saveData["hero"]["name"] = hero->getName();
        saveData["hero"]["health"] = hero->getHealth().health;
        saveData["hero"]["maxHealth"] = hero->getHealth().maxHealth;
        saveData["hero"]["defense"] = hero->getHealth().defense;
        saveData["hero"]["focus"] = hero->getFocus();
        saveData["hero"]["money"] = hero->getMoney();

        json manaArray = json::array();
        for (int i = 0; i < 5; ++i) {
            manaArray.push_back(hero->getMana(static_cast<Element>(i)));
        }
        saveData["hero"]["mana"] = manaArray;

        json spellBookArray = json::array();
        const SpellBook& spellBook = hero->getSpellBook();


        for (int i = 0; i < spellBook.getSpellCount(); ++i) {
            Spell* spell = spellBook.getSpell(i);
            json spellData;
            spellData["spells"].push_back(serializeSpell(*spell));
            spellBookArray.push_back(spellData);
        }


        saveData["hero"]["spellBook"] = spellBookArray;

        saveData["isAmuletFounded"] = static_cast<bool>(isAmuletFounded);
        saveData["isBarierDestroyed"] = static_cast<bool>(isBarierDestroyed);
        saveData["currentStageName"] = storyManager.getCurrentStage().get()->getDescription();

        std::ofstream file(filename);

        if (!file.is_open())
        {
            qInfo() << "Ошибка при открытии файла сохранения";
            return;
        }

        file << saveData.dump(4);
        file.close();


        qInfo() << "Игра сохранена в " << QString::fromStdString(filename);



    }
    catch (const std::exception& e) {
        qInfo() << "Ошибка сохранения: " << e.what();

    }
}

void Game::startBattle(Enemy& enemy) {
    currentBattle = new Battle(*hero, enemy, this, this->gameWindow);
    currentBattle->processBattle();
}


void Game::showMerchantOptions() {
    gameWindow->updateButtons({
        {"Купить Зелье Здоровья (-500)", [this]() { processPurchase("Зелье здоровья", 500, 1); }},
        {"Купить Зелье Маны (-500)", [this]() { processPurchase("Зелье маны", 500, 2); }},
        {"Купить Зелье Сосредоточения (-700)", [this]() { processPurchase("Зелье сосредоточения", 700, 3); }},
        {"Купить Амулет Силы (-700)", [this]() { processPurchase("Амулет силы", 700, 4); }},
        {"Купить Амулет маны (-600)", [this]() { processPurchase("Амулет маны", 600, 5); }},
        {"Вернуться", [this]() { storyManager.restartStage("Хижина Путника"); }}
        });
}

void Game::processPurchase(const QString& item, int cost, int itemType) {
    if (hero.get()->getMoney() >= cost) {

        hero.get()->setMoney(hero.get()->getMoney() - cost);
        switch (itemType) {
        case 1:
            hero.get()->restoreHealth(40);
            break;
        case 2:
            for (int i = 0; i < 5; i++) {
				hero.get()->setMana(i, hero.get()->getMana(static_cast<Element>(i)) + 40);
                if(hero.get()->getMana(static_cast<Element>(i)) > 100) {
					hero.get()->setMana(i, 100);
				}
            }
            break;
        case 3:
            hero.get()->setFocus(hero.get()->getFocus() + 40);
            break;
        case 4:
            hero.get()->setMana(static_cast<int>(Element::Spirit), hero.get()->getMana(Element::Spirit) + 20);
            hero.get()->setMana(static_cast<int>(Element::Air), hero.get()->getMana(Element::Air) + 20);
            hero.get()->setMana(static_cast<int>(Element::Earth), hero.get()->getMana(Element::Earth) + 20);
            break;
        case 5:
            hero.get()->setMana(static_cast<int>(Element::Water), hero.get()->getMana(Element::Water) + 20);
            hero.get()->setMana(static_cast<int>(Element::Fire), hero.get()->getMana(Element::Fire) + 20);
            break;
        }
    }
    else {
        qDebug() << "Not enough money for" << item;
    }
}

void Game::displayBattle(const QString& enemy) {
    QString battleText = QString("Here will be a battle with %1.").arg(enemy);
    gameWindow->ui.label->setText(battleText);

    gameWindow->updateButtons({
        {"Return to Cabin", [this]() { storyManager.restartStage("Traveler's Cabin"); }}
        });
}

void Game::useAltarOfPower() {
    
    if (hero->getMoney() >= 1000) {
        hero->setMoney(hero->getMoney() - 1000);
        hero->setMana(static_cast<int>(Element::Spirit), hero->getMana(Element::Spirit) + 50);
        hero->setMana(static_cast<int>(Element::Air), hero->getMana(Element::Air) + 50);
        hero->setMana(static_cast<int>(Element::Earth), hero->getMana(Element::Earth) + 50);
        hero->setMana(static_cast<int>(Element::Fire), hero->getMana(Element::Fire) + 50);
        hero->setMana(static_cast<int>(Element::Water), hero->getMana(Element::Water) + 50);
        qDebug() << "Герой усилился у Алтаря Силы.";
        storyManager.restartStage("Хижина Путника");
    }
    else {
        qDebug() << "Недостаточно денег для использования алтаря.";
        storyManager.restartStage("Хижина Путника");
    }
}
void Game::initializeEnemies() {
    enemies = new Enemy[3]{
       Enemy("Волки", 50, 20),
       Enemy("Призрачный Страж", 100, 30),
       Enemy("Смертоносец", 200, 50)
    };
}

void Game::displayWorldMap() {
    gameWindow->updateButtons({
        {"Лесной Перекресток", [this]() { storyManager.completeCurrentStage(); storyManager.restartStage("Лесной Перекресток"); }},
        {"Пещера Призраков", [this]() {  storyManager.completeCurrentStage(); storyManager.restartStage("Пещера Призраков"); }},
        {"Логово Смертоносца", [this]() {
                storyManager.completeCurrentStage();
                storyManager.restartStage("Логово Смертоносца");
}},
{"Вернуться в хижину", [this]() { storyManager.restartStage("Хижина Путника"); }}
        });
}