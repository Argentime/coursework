#include "functions.h"

using namespace std;

class Spell {
public:
    string name;
    Element element1;
    Element element2;
    int damage;

    // ����������� ����������
    Spell(string n, Element el1, Element el2, int dmg)
        : name(n), element1(el1), element2(el2), damage(dmg) {}

    // ����� ���������� � ����������
    void display() const {
        cout << name
             << ": " << elementToString(element1)
             << " + " << elementToString(element2)
             << ", ����: " << damage << endl;
    }
};

class SpellBook {
private:
    Spell** spells;
    int spellCount;

public:
    SpellBook() : spells(nullptr), spellCount(0) {}

    ~SpellBook() {
        for (int i = 0; i < spellCount; ++i) {
            delete spells[i];
        }
        delete[] spells;
    }

    // ���������� ����������
    void addSpell(string name, Element el1, Element el2, int damage) {
        Spell** newSpells = new Spell * [spellCount + 1];
        for (int i = 0; i < spellCount; ++i) {
            newSpells[i] = spells[i];
        }
        newSpells[spellCount] = new Spell(name, el1, el2, damage);
        delete[] spells;
        spells = newSpells;
        spellCount++;
    }

    // ����������� ���� ����������
    void displaySpells() const {
        for (int i = 0; i < spellCount; ++i) {
            spells[i]->display();
        }
    }

    // ���������� ���������� �� �����
    void updateSpell(string oldName, string newName, int newDamage) {
        for (int i = 0; i < spellCount; ++i) {
            if (spells[i]->name == oldName) {
                spells[i]->name = newName;
                spells[i]->damage = newDamage;
                cout << "���������� ���������.\n";
                return;
            }
        }
        cout << "���������� � ����� ������ �� �������.\n";
    }

    // �������� ����������
    void removeSpell(string name) {
        int index = -1;
        for (int i = 0; i < spellCount; ++i) {
            if (spells[i]->name == name) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "���������� � ����� ������ �� �������.\n";
            return;
        }

        Spell** newSpells = new Spell * [spellCount - 1];
        for (int i = 0, j = 0; i < spellCount; ++i) {
            if (i != index) {
                newSpells[j++] = spells[i];
            }
        }
        delete spells[index];
        delete[] spells;
        spells = newSpells;
        spellCount--;
        cout << "���������� �������.\n";
    }
};

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
            cin >> name;
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
            string oldName, newName;
            int newDamage;

            cout << "������� �������� ���������� ��� ����������: ";
            cin >> oldName;
            cout << "������� ����� �������� ����������: ";
            cin >> newName;
            cout << "������� ����� ���� ����������: ";
            cin >> newDamage;

            mySpellBook.updateSpell(oldName, newName, newDamage);

        }
        else if (choice == 4) {
            string name;

            cout << "������� �������� ���������� ��� ��������: ";
            cin >> name;

            mySpellBook.removeSpell(name);
        }

    } while (choice != 0);

    cout << "����� �� ���������.\n";
    return 0;
}
