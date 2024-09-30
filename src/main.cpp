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

        case 5: {
            string name;

            cout << "������� �������� ���������� ��� �������������: ";
            getline(cin, name);

            mySpellBook.castSpell(name);
            break;
        }
        case 0: {
            cout << "����� �� ���������.\n";
            return 0;
        }
        default: {
            cout << "������� ����� �� 1 �� 5 ���� 0.\n";
        }
        }
    } while (!choice);
}