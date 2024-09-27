#include "functions.h"
#include "Spell.h"
#include "SpellBook.h"

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

        if (choice == 1) {
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

        }
        else if (choice == 2) {
            mySpellBook.displaySpells();

        }
        else if (choice == 3) {
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

        }
        else if (choice == 4) {
            string name;

            cout << "������� �������� ���������� ��� ��������: ";
            getline(cin, name);

            mySpellBook.removeSpell(name);
        }
        else if (choice == 5) {
            string name;

            cout << "������� �������� ���������� ��� �������������: ";
            getline(cin, name);

            mySpellBook.castSpell(name);
        }

    } while (choice != 0);

    cout << "����� �� ���������.\n";
    return 0;
}
