#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class Spell {
public:
    string name;
    string element1;
    string element2;
    int damage;

    Spell(string n, string e1, string e2, int d) : name(n), element1(e1), element2(e2), damage(d) {}

    void display() const{
        cout << "����������: " << name << ", ��������: " << element1 << " + " << element2 << ", ����: " << damage << endl;
    }
};

class SpellBook {
private:
    Spell** spells;   // ��������� ��������� ��� ������������� ������� ����������
    int spellCount;   // ���������� ����������

public:
    SpellBook() : spells(nullptr), spellCount(0) {}

    // ���������� ����������
    void addSpell(string name, string element1, string element2, int damage) {
        // �������� ������ ������� �������� �� 1 ������
        Spell** newSpells = new Spell * [spellCount + 1];

        // ����������� ������������ ���������� � ����� ������
        for (int i = 0; i < spellCount; ++i) {
            newSpells[i] = spells[i];
        }

        // �������� ������ ����������
        newSpells[spellCount] = new Spell(name, element1, element2, damage);

        // �������� ������� �������
        delete[] spells;

        // ����������� ����� ������
        spells = newSpells;

        // ����������� ���������� ����������
        spellCount++;
    }

    // ����� ���� ����������
    void displaySpells() const {
        if (spellCount == 0) {
            cout << "���������� ���." << endl;
            return;
        }

        for (int i = 0; i < spellCount; ++i) {
            spells[i]->display();
        }
    }

    // ���������� ����������
    void updateSpell(string oldName, string newName, int newDamage) {
        for (int i = 0; i < spellCount; ++i) {
            if (spells[i]->name == oldName) {
                spells[i]->name = newName;
                spells[i]->damage = newDamage;
                cout << "���������� ���������." << endl;
                return;
            }
        }
        cout << "���������� �� �������." << endl;
    }

    // �������� ����������
    void removeSpell(string name) {
        bool found = false;
        for (int i = 0; i < spellCount; ++i) {
            if (spells[i]->name == name) {
                found = true;
                // ������� ����������
                delete spells[i];

                // �������� ��� �������� ������� �� ���� ������� �����
                for (int j = i; j < spellCount - 1; ++j) {
                    spells[j] = spells[j + 1];
                }

                // ��������� ������ �������
                spellCount--;
                break;
            }
        }

        if (found) {
            // ������� ����� ������ �������� �� 1 ������
            Spell** newSpells = new Spell * [spellCount];

            // �������� ���������� ����������
            for (int i = 0; i < spellCount; ++i) {
                newSpells[i] = spells[i];
            }

            // ������� ������ ������
            delete[] spells;

            // ����������� ����� ������
            spells = newSpells;

            cout << "���������� �������." << endl;
        }
        else {
            cout << "���������� �� �������." << endl;
        }
    }

    // ���������� ��� ������������ ������
    ~SpellBook() {
        for (int i = 0; i < spellCount; ++i) {
            delete spells[i];
        }
        delete[] spells;
    }
};

int main() {
    
    SetConsoleOutputCP(1251);

    SpellBook mySpellBook;

    // ������ ���������� ����������
    mySpellBook.addSpell("������", "�����", "�����", 50);
    mySpellBook.addSpell("������", "����", "�����", 40);

    cout << "������ ����������:" << endl;
    mySpellBook.displaySpells();

    // ���������� ����������
    mySpellBook.updateSpell("������", "������� ������", 60);

    // �������� ����������
    mySpellBook.removeSpell("������");

    cout << "����������� ������ ����������:" << endl;
    mySpellBook.displaySpells();

    return 0;
}
