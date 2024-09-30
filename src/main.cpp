#include "header/functions.h"
#include "header/Spell.h"
#include "header/SpellBook.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SpellBook mySpellBook;
    int choice;

    do {
        printMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1: {
            string name;
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

        case 5: {
            string name;

            cout << "Введите название заклинания для использования: ";
            getline(cin, name);

            mySpellBook.castSpell(name);
            break;
        }
        case 0: {
            cout << "Выход из программы.\n";
            return 0;
        }
        default: {
            cout << "Введите число от 1 до 5 либо 0.\n";
        }
        }
    } while (!choice);
}