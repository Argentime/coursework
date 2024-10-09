#include "header/functions.h"
#include "header/Spell.h"
#include "header/SpellBook.h"
#include "header/Character.h"
#include "header/nlohmann/json.hpp"
#include <fstream>

using namespace std;
using json = nlohmann::json;

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
    } while (choice != (1||2));

    
}