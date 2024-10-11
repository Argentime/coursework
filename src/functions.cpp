#include "header/functions.h"

#include <fstream>

using namespace std;
using json = nlohmann::json;

bool operator==(HealthStats hp, int percent);

void printMenu(int var) {
    switch (var) {
    case 1:
        cout << "\n����:\n";
        cout << "1. ������ �����\n";
        cout << "2. �����������\n";
        cout << "3. ������� ����� ����������\n";
        cout << "4. ������������ ���������� �� ����\n";
        cout << "0. ��������� � �����\n";
        cout << "��� �����: ";
        break;
    case 2:
        cout << "����� ������� �� ������ ���������������� �����:\n";
        cout << "1. �������\n";
        cout << "2. ������� �������������� �������\n";
        break;
    case 3:
        cout << "\n���� ����������:\n";
        cout << "1. �������� ����������\n";
        cout << "2. ������� ����������\n";
        cout << "3. �������� ����������\n";
        cout << "4. ������� ����������\n";
        cout << "0. �����\n";
        break;
    case 4:
        cout << "\n���� �������� �����:\n";
        cout << "1. �������� ���\n";
        cout << "2. ���������� ������� ����������� ��\n";
        cout << "3. ���������� ������������ ����������� ��\n";
        cout << "4. ���������� ����������� ������\n";
        cout << "5. ���������� �����������������\n";
        cout << "0. �����\n";
        break;
    }
}

string elementToString(Element el) {
    using enum Element;
    switch (el) {
        
    case Fire: return "�����";
    case Earth: return "�����";
    case Water: return "����";
    case Air: return "������";
    case Spirit: return "���";
    default: return "����������� ������";
    }
}

Element selectElement() {
    int choice;
    cout << "�������� ������:\n";
    cout << "0 - �����\n";
    cout << "1 - �����\n";
    cout << "2 - ����\n";
    cout << "3 - ������\n";
    cout << "4 - ���\n";
    cout << "��� �����: ";
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

void saveHeroToJson(const Hero& hero, const std::string& filename) {

    json heroJson;

    heroJson["spells"] = json::array();
    heroJson["h_mana"] = json::array();
    heroJson["h_money"] = hero.getMoney();
    heroJson["h_name"] = win1251ToUtf8(hero.getName());
    heroJson["h_hp"] = hero.getHealth().health;
    heroJson["h_maxHp"] = hero.getHealth().maxHealth;
    heroJson["h_defence"] = hero.getHealth().defense;
    heroJson["h_focus"] = hero.getFocus();

    for (int i = 0; i < hero.getSpellBook().getSpellCount(); ++i) {
        heroJson["spells"].push_back(serializeSpell(*hero.getSpellBook().getSpells()[i]));
    }

    for (int i = 0; i < 5; ++i) {
        heroJson["h_mana"].push_back(hero.getMana(Element(i)));
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << heroJson.dump(4);
        file.close();
    }
    else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}

void loadHeroFromJson(Hero& hero, const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        json heroJson;
        file >> heroJson;
        file.close();

        HealthStats hp;
        
        hp.defense = heroJson.at("h_defence").get<float>();
        hp.health = heroJson.at("h_hp").get<int>();
        hp.maxHealth = heroJson.at("h_maxHp").get<int>();
        string name = utf8ToWin1251(heroJson.at("h_name").get<string>());
        int focus = heroJson.at("h_focus").get<int>();
        int money = heroJson.at("h_money").get<int>();
        auto mana = new int[static_cast<int>(Element::Spirit) + 1];
        

        for (int i = 0; i < 5; ++i) {
            mana[i] = heroJson.at("h_mana").at(i).get<int>();
        }

        Hero bufHero(name, hp, focus, money, mana);
        

        for (const auto& spellJson : heroJson.at("spells")) {
            Spell spell = deserializeSpell(spellJson);
            bufHero.getSpellBook().addSpell(spell.name, spell.element1, spell.element2, spell.damage);
        }
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
            cout << "������� �������� ����������: ";
            getline(cin, name);
            Element el1 = selectElement();
            Element el2 = selectElement();
            cout << "������� ���� ����������: ";
            cin >> damage;

            mySpellBook.addSpell(name, el1, el2, damage);
            cout << "���������� ���������.\n";
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

            cout << "������� �������� ���������� ��� ����������: ";
            getline(cin, oldName);
            cout << "������� ����� �������� ����������: ";
            getline(cin, newName);
            cout << "������� ����� ���� ����������: ";
            cin >> newDamage;
            mySpellBook.updateSpell(oldName, newName, newDamage);
            break;
        }

        case 4: {
            string newName;

            cout << "������� �������� ���������� ��� ��������: ";
            getline(cin, name);

            mySpellBook.removeSpell(name);
            break;
        }
        case 0: {
            break;
        }
        default: {
            cout << "������� ����� �� 1 �� 4 ���� 0.\n";
        }
        }
    } while (ch);
}

void manageHero(Hero& hero) {
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
            cout << "������� ��� �����: ";
            getline(cin, name);
            hero.setName(name);
            cout << "��� ����� ������������.\n";
            break;
        }

        case 2: {
            cout << "���������� ������� ����������� ��\n";
            cin >> hp.health;
            hero.setHealth(hp.health,-1,-1);
            break;
        }

        case 3: {
            cout << "���������� ������������ ����������� ��\n";
            cin >> hp.maxHealth;
            hero.setHealth(-1, -1, hp.maxHealth);
            break;
        }

        case 4: {
            cout << "���������� ����������� ������\n";
            cin >> hp.defense;
            hero.setHealth(-1, hp.defense, -1);
            break;
        }
        case 5: {
            cout << "���������� �����������������\n";
            cin >> focus;
            hero.setFocus(focus);
            break;
        }
        case 0: {
            break;
        }
        default: {
            cout << "������� ����� �� 1 �� 5 ���� 0.\n";
        }
        }
    } while (ch);
}
