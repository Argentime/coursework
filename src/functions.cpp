#include "header/functions.h"

#include <fstream>

using namespace std;
using json = nlohmann::json;

bool operator==(HealthStats hp, int percent);

void printMenu(int var) {
    switch (var) {
    case 1:
        cout << "\nМеню:\n";
        cout << "1. Статус героя\n";
        cout << "2. Осмотреться\n";
        cout << "3. Открыть книгу заклинаний\n";
        cout << "4. Использовать заклинание\n";
        cout << "0. Сохранить и выйти\n";
        cout << "Ваш выбор: ";
        break;
    case 2:
        cout << "Каким образом вы хотите инициализировать героя:\n";
        cout << "1. Вручную\n";
        cout << "2. Заранее подготовленный вариант\n";
        break;
    case 3:
        cout << "\nМеню заклинаний:\n";
        cout << "1. Добавить заклинание\n";
        cout << "2. Вывести заклинания\n";
        cout << "3. Обновить заклинание\n";
        cout << "4. Удалить заклинание\n";
        cout << "0. Выйти\n";
        break;
    case 4:
        cout << "\nМеню создания героя:\n";
        cout << "1. Добавить имя\n";
        cout << "2. Установить текущее колличество хп\n";
        cout << "3. Установить максимальное колличество хп\n";
        cout << "4. Установить колличество защиты\n";
        cout << "5. Установить сосредоточенность\n";
        cout << "0. Выйти\n";
        break;
    }
}

string elementToString(Element el) {
    using enum Element;
    switch (el) {
        
    case Fire: return "Огонь";
    case Earth: return "Земля";
    case Water: return "Вода";
    case Air: return "Воздух";
    case Spirit: return "Дух";
    default: return "Неизвестная стихия";
    }
}

Element selectElement() {
    int choice;
    cout << "Выберите стихию:\n";
    cout << "0 - Огонь\n";
    cout << "1 - Земля\n";
    cout << "2 - Вода\n";
    cout << "3 - Воздух\n";
    cout << "4 - Дух\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    

    return Element(choice);
}


string win1251ToUtf8(const string& win1251Str) {
    int wcharsCount = MultiByteToWideChar(1251, 0, win1251Str.c_str(), -1, nullptr, 0);
    auto wstr = new wchar_t[wcharsCount];
    MultiByteToWideChar(1251, 0, win1251Str.c_str(), -1, wstr, wcharsCount);

    int utf8CharCount = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    auto utf8Str = new char[utf8CharCount];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8Str, utf8CharCount, nullptr, nullptr);

    string result(utf8Str);
    delete[] wstr;
    delete[] utf8Str;
    return result;
}

string utf8ToWin1251(const string& utf8Str) {
    int wcharsCount = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
    auto wstr = new wchar_t[wcharsCount];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wstr, wcharsCount);

    int win1251CharCount = WideCharToMultiByte(1251, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    auto win1251Str = new char[win1251CharCount];
    WideCharToMultiByte(1251, 0, wstr, -1, win1251Str, win1251CharCount, nullptr, nullptr);

    string result(win1251Str);
    delete[] wstr;
    delete[] win1251Str;
    return result;
}

json serializeSpell(const Spell& spell) {
    return json{
        {"name", win1251ToUtf8(spell.name)},
        {"element1", spell.element1},
        {"element2", spell.element2},
        {"damage", spell.damage},
        {"uses", spell.uses}
    };
}

Spell deserializeSpell(const json& j) {
    string name = utf8ToWin1251(j.at("name").get<string>());
    auto el1 = static_cast<Element>(j.at("element1").get<int>());
    auto el2 = static_cast<Element>(j.at("element2").get<int>());
    int damage = j.at("damage").get<int>();
    int uses = j.at("uses").get<int>();

    Spell spell(name, el1, el2, damage);
    spell.uses = uses;

    return spell;
}

void saveSpellBookToJson(const Character& hero, const SpellBook& spellBook, const std::string& filename) {

    json spellBookJson;

    spellBookJson["spells"] = json::array();
    spellBookJson["h_name"] = hero.getName();
    spellBookJson["h_hp"] = hero.getHealth().health;
    spellBookJson["h_maxHp"] = hero.getHealth().maxHealth;
    spellBookJson["h_defence"] = hero.getHealth().defense;
    spellBookJson["h_focus"] = hero.getFocus();

    for (int i = 0; i < spellBook.getSpellCount(); ++i) {
        spellBookJson["spells"].push_back(serializeSpell(*spellBook.getSpells()[i]));
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << spellBookJson.dump(4);
        file.close();
    }
    else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}

void loadSpellBookFromJson(Character& hero,SpellBook& spellBook, const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        json spellBookJson;
        file >> spellBookJson;
        file.close();

        HealthStats hp;
        
        hp.defense = spellBookJson.at("h_defence").get<float>();
        hp.health = spellBookJson.at("h_hp").get<int>();
        hp.maxHealth = spellBookJson.at("h_maxHp").get<int>();
        string name = spellBookJson.at("h_name").get<string>(); 
        int focus = spellBookJson.at("h_focus").get<int>();

        for (const auto& spellJson : spellBookJson.at("spells")) {
            Spell spell = deserializeSpell(spellJson);
            spellBook.addSpell(spell.name, spell.element1, spell.element2, spell.damage);
        }
        Character bufHero(name, hp, focus);
        hero = bufHero;
    }
    else {
        std::cerr << "Error: Could not open file for reading." << std::endl;
    }
}


void manageSpellBook(SpellBook& mySpellBook) {
    int ch;

    do {
        printMenu(3);
        cin >> ch;
        cin.ignore();
        string name;

        switch (ch) {

        case 1: {
            int damage;
            cout << "Введите название заклинания: ";
            getline(cin, name);
            Element el1 = selectElement();
            Element el2 = selectElement();
            cout << "Введите урон заклинания: ";
            cin >> damage;

            mySpellBook.addSpell(name, el1, el2, damage);
            cout << "Заклинание добавлено.\n";
            break;
        }

        case 2: {
            cout << mySpellBook;
            break;
        }

        case 3: {
            string oldName;
            string newName;
            int newDamage;

            cout << "Введите название заклинания для обновления: ";
            getline(cin, oldName);
            cout << "Введите новое название заклинания: ";
            getline(cin, newName);
            cout << "Введите новый урон заклинания: ";
            cin >> newDamage;
            mySpellBook.updateSpell(oldName, newName, newDamage);
            break;
        }

        case 4: {
            string newName;

            cout << "Введите название заклинания для удаления: ";
            getline(cin, name);

            mySpellBook.removeSpell(name);
            break;
        }
        case 0: {
            break;
        }
        default: {
            cout << "Введите число от 1 до 4 либо 0.\n";
        }
        }
    } while (ch);
}

void manageHero(Character& hero) {
    int ch;

    do {
        printMenu(4);
        cin >> ch;
        cin.ignore();
        string name;
        HealthStats hp;
        int focus;

        switch (ch) {

        case 1: {
            cout << "Введите имя героя: ";
            getline(cin, name);
            hero.setName(name);
            cout << "Имя героя установленно.\n";
            break;
        }

        case 2: {
            cout << "Установите текущее колличество хп\n";
            cin >> hp.health;
            hero.setHealth(hp.health,-1,-1);
            break;
        }

        case 3: {
            cout << "Установите максимальное колличество хп\n";
            cin >> hp.maxHealth;
            hero.setHealth(-1, -1, hp.maxHealth);
            break;
        }

        case 4: {
            cout << "Установите колличество защиты\n";
            cin >> hp.defense;
            hero.setHealth(-1, hp.defense, -1);
            break;
        }
        case 5: {
            cout << "Установите сосредоточенность\n";
            cin >> focus;
            hero.setFocus(focus);
            break;
        }
        case 0: {
            break;
        }
        default: {
            cout << "Введите число от 1 до 5 либо 0.\n";
        }
        }
    } while (ch);
}
