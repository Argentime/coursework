#include "header/functions.h"
#include "header/Spell.h"
#include "header/SpellBook.h"
#include "header/Character.h"
#include <fstream>
#include "header/nlohmann/json.hpp"

using namespace std;

using json = nlohmann::json;



json serializeSpell(const Spell& spell) {
    return json{
        {"name", spell.name},
        {"element1", spell.element1},
        {"element2", spell.element2},
        {"damage", spell.damage},
        {"uses", spell.uses}
    };
}

Spell deserializeSpell(const json& j) {
    std::string name = j.at("name").get<std::string>();
    Element el1 = static_cast<Element>(j.at("element1").get<int>());
    Element el2 = static_cast<Element>(j.at("element2").get<int>());
    int damage = j.at("damage").get<int>();
    int uses = j.at("uses").get<int>();

    Spell spell(name, el1, el2, damage);
    spell.uses = uses;

    return spell;
}

void saveSpellBookToJson(const SpellBook& spellBook, const std::string& filename) {
    json spellBookJson;

    spellBookJson["spellCount"] = spellBook.spellCount;
    spellBookJson["spells"] = json::array();

    for (int i = 0; i < spellBook.spellCount; ++i) {
        spellBookJson["spells"].push_back(serializeSpell(*spellBook.spells[i]));
    }

    // ��������� JSON � ����
    std::ofstream file(filename);
    if (file.is_open()) {
        file << spellBookJson.dump(4); // 4 - ������� ��� ������� ��������������
        file.close();
    }
    else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}

void loadSpellBookFromJson(SpellBook& spellBook, const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        json spellBookJson;
        file >> spellBookJson;
        file.close();

        // ��������� ����������
        int spellCount = spellBookJson.at("spellCount").get<int>();

        for (const auto& spellJson : spellBookJson.at("spells")) {
            Spell spell = deserializeSpell(spellJson);
            spellBook.addSpell(spell.name, spell.element1, spell.element2, spell.damage);
        }
    }
    else {
        std::cerr << "Error: Could not open file for reading." << std::endl;
    }
}

void manageSpellBook(SpellBook mySpellBook) {
    int choice;

    do {
        printMenu(3);
        cin >> choice;
        cin.ignore();
        string name;

        switch (choice) {

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
            mySpellBook.displaySpells();
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
            string name;

            cout << "������� �������� ���������� ��� ��������: ";
            getline(cin, name);

            mySpellBook.removeSpell(name);
            break;
        }
        case 0: {
            saveSpellBookToJson(mySpellBook, "spellbook.json");
            cout << "����� �� ����.\n";
            return;
        }
        default: {
            cout << "������� ����� �� 1 �� 5 ���� 0.\n";
        }
        }
    } while (choice);
}

int main() {
   
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SpellBook mySpellBook;
    Character hero("Test", 100, 100);
    int choice;

    do {
        printMenu(2);
        cin >> choice;
        switch (choice) {
        case 1: {
            manageSpellBook(mySpellBook);
            break;
        }
        case 2: {
            loadSpellBookFromJson(mySpellBook, "spellbook.json");
            manageSpellBook(mySpellBook);
            break;
        }
        default: {
            cout << "������� ����� 1 ���� 2.\n";
        }
        }
    } while (choice != (1 || 2));

    
}