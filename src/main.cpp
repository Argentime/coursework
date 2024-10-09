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
            mySpellBook.displaySpells();
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
            string name;

            cout << "Введите название заклинания для удаления: ";
            getline(cin, name);

            mySpellBook.removeSpell(name);
            break;
        }
        case 0: {
            saveSpellBookToJson(mySpellBook, "spellbook.json");
            cout << "Выход из меню.\n";
            return;
        }
        default: {
            cout << "Введите число от 1 до 5 либо 0.\n";
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
            cout << "Введите число 1 либо 2.\n";
        }
        }
    } while (choice != (1||2));

    
}