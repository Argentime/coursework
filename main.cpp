#include "functions.h"

using namespace std;

class Spell {
public:
    string name;
    Element element1;
    Element element2;
    int damage;

    Spell(string const &n, Element el1, Element el2, int dmg)
        : name(n), element1(el1), element2(el2), damage(dmg) {}

    void display() const {
        cout << name
             << ": " << elementToString(element1)
             << " + " << elementToString(element2)
             << ", Урон: " << damage << endl;
    }
};

class SpellBook {
private:
    Spell** spells = nullptr;
    int spellCount=0;

public:

    ~SpellBook() {
        for (int i = 0; i < spellCount; ++i) {
            delete spells[i];
        }
        delete[] spells; 
    }

    void addSpell(string const &name, Element el1, Element el2, int damage) {
        auto newSpells = new Spell * [spellCount + 1];
        for (int i = 0; i < spellCount; ++i) {
            newSpells[i] = spells[i];
        }
        newSpells[spellCount] = new Spell(name, el1, el2, damage);
        delete[] spells;
        spells = newSpells;
        spellCount++;
    }

    void displaySpells() const {
        if (spellCount == 0) {
            cout << "Заклинаний нет. \n";
        }
        else {
            for (int i = 0; i < spellCount; ++i) {
                spells[i]->display();
            }
        }
    }

    // Обновление заклинания по имени
    void updateSpell(string const &oldName, string const &newName, int newDamage) {
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
    void removeSpell(string const &name) {
        Spell* spellToRemove = findSpellByName(name);
        if (spellToRemove == nullptr) {
            cout << "Заклинание с таким именем не найдено.\n";
            return;
        }

        for (int i = 0; i < spellCount; ++i) {
            if (spells[i] == spellToRemove) {
                delete spells[i]; 
                for (int j = i; j < spellCount - 1; ++j) {
                    spells[j] = spells[j + 1];
                }
                spellCount--; 
                spells[spellCount] = nullptr;
                cout << "Заклинание удалено.\n";
                return;
            }
        } 
    }

    Spell* findSpellByName(string const& name) const {
        for (int i = 0; i < spellCount; ++i) {
            if (spells[i]->name == name) {
                return spells[i];
            }
        }
        return nullptr;
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
            getline(cin, name);
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
            string oldName;
            string newName;
            int newDamage;
            cin.ignore();

            cout << "Введите название заклинания для обновления: ";
            getline(cin, oldName);
            cout << "Введите новое название заклинания: ";
            getline(cin, newName);
            cout << "Введите новый урон заклинания: ";
            cin >> newDamage;

            mySpellBook.updateSpell(oldName, newName, newDamage);

        }
        else if (choice == 4) {
            string name;

            cout << "Введите название заклинания для удаления: ";
            getline(cin, name);

            mySpellBook.removeSpell(name);
        }

    } while (choice != 0);

    cout << "Выход из программы.\n";
    return 0;
}
