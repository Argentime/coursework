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
        cout << "Заклинание: " << name << ", Элементы: " << element1 << " + " << element2 << ", Урон: " << damage << endl;
    }
};

class SpellBook {
private:
    Spell** spells;   // Двумерный указатель для динамического массива заклинаний
    int spellCount;   // Количество заклинаний

public:
    SpellBook() : spells(nullptr), spellCount(0) {}

    // Добавление заклинания
    void addSpell(string name, string element1, string element2, int damage) {
        // Создание нового массива размером на 1 больше
        Spell** newSpells = new Spell * [spellCount + 1];

        // Копирование существующих заклинаний в новый массив
        for (int i = 0; i < spellCount; ++i) {
            newSpells[i] = spells[i];
        }

        // Создание нового заклинания
        newSpells[spellCount] = new Spell(name, element1, element2, damage);

        // Удаление старого массива
        delete[] spells;

        // Присваиваем новый массив
        spells = newSpells;

        // Увеличиваем количество заклинаний
        spellCount++;
    }

    // Вывод всех заклинаний
    void displaySpells() const {
        if (spellCount == 0) {
            cout << "Заклинаний нет." << endl;
            return;
        }

        for (int i = 0; i < spellCount; ++i) {
            spells[i]->display();
        }
    }

    // Обновление заклинания
    void updateSpell(string oldName, string newName, int newDamage) {
        for (int i = 0; i < spellCount; ++i) {
            if (spells[i]->name == oldName) {
                spells[i]->name = newName;
                spells[i]->damage = newDamage;
                cout << "Заклинание обновлено." << endl;
                return;
            }
        }
        cout << "Заклинание не найдено." << endl;
    }

    // Удаление заклинания
    void removeSpell(string name) {
        bool found = false;
        for (int i = 0; i < spellCount; ++i) {
            if (spells[i]->name == name) {
                found = true;
                // Удаляем заклинание
                delete spells[i];

                // Сдвигаем все элементы массива на одну позицию влево
                for (int j = i; j < spellCount - 1; ++j) {
                    spells[j] = spells[j + 1];
                }

                // Уменьшаем размер массива
                spellCount--;
                break;
            }
        }

        if (found) {
            // Создаем новый массив размером на 1 меньше
            Spell** newSpells = new Spell * [spellCount];

            // Копируем оставшиеся заклинания
            for (int i = 0; i < spellCount; ++i) {
                newSpells[i] = spells[i];
            }

            // Удаляем старый массив
            delete[] spells;

            // Присваиваем новый массив
            spells = newSpells;

            cout << "Заклинание удалено." << endl;
        }
        else {
            cout << "Заклинание не найдено." << endl;
        }
    }

    // Деструктор для освобождения памяти
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

    // Пример добавления заклинаний
    mySpellBook.addSpell("Метеор", "Огонь", "Земля", 50);
    mySpellBook.addSpell("Гейзер", "Вода", "Земля", 40);

    cout << "Список заклинаний:" << endl;
    mySpellBook.displaySpells();

    // Обновление заклинания
    mySpellBook.updateSpell("Гейзер", "Сильный Гейзер", 60);

    // Удаление заклинания
    mySpellBook.removeSpell("Метеор");

    cout << "Обновленный список заклинаний:" << endl;
    mySpellBook.displaySpells();

    return 0;
}
