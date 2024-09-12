#include "functions.h"

using namespace std;

class Spell {
public:
    string name;
    Element element1;
    Element element2;
    int damage;

    // Конструктор заклинания
    Spell(string n, Element el1, Element el2, int dmg)
        : name(n), element1(el1), element2(el2), damage(dmg) {}

    // Вывод информации о заклинании
    void display() const {
        cout << name
             << ": " << elementToString(element1)
             << " + " << elementToString(element2)
             << ", Урон: " << damage << endl;
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

    // Добавление заклинания
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

    // Отображение всех заклинаний
    void displaySpells() const {
        for (int i = 0; i < spellCount; ++i) {
            spells[i]->display();
        }
    }

    // Обновление заклинания по имени
    void updateSpell(string oldName, string newName, int newDamage) {
        for (int i = 0; i < spellCount; ++i) {
            if (spells[i]->name == oldName) {
                spells[i]->name = newName;
                spells[i]->damage = newDamage;
                cout << "Заклинание обновлено.\n";
                return;
            }
        }
        cout << "Заклинание с таким именем не найдено.\n";
    }

    // Удаление заклинания
    void removeSpell(string name) {
        int index = -1;
        for (int i = 0; i < spellCount; ++i) {
            if (spells[i]->name == name) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Заклинание с таким именем не найдено.\n";
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
        cout << "Заклинание удалено.\n";
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

            cout << "Введите название заклинания: ";
            cin >> name;
            Element el1 = selectElement();
            Element el2 = selectElement();
            cout << "Введите урон заклинания: ";
            cin >> damage;

            mySpellBook.addSpell(name, el1, el2, damage);
            cout << "Заклинание добавлено.\n";

        }
        else if (choice == 2) {
            mySpellBook.displaySpells();

        }
        else if (choice == 3) {
            string oldName, newName;
            int newDamage;

            cout << "Введите название заклинания для обновления: ";
            cin >> oldName;
            cout << "Введите новое название заклинания: ";
            cin >> newName;
            cout << "Введите новый урон заклинания: ";
            cin >> newDamage;

            mySpellBook.updateSpell(oldName, newName, newDamage);

        }
        else if (choice == 4) {
            string name;

            cout << "Введите название заклинания для удаления: ";
            cin >> name;

            mySpellBook.removeSpell(name);
        }

    } while (choice != 0);

    cout << "Выход из программы.\n";
    return 0;
}
