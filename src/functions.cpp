#include "header/functions.h"
#include "header/Spell.h"
#include "header/SpellBook.h"
#include "header/Character.h"

using namespace std;

void printMenu(int var) {
    switch (var) {
    case 1:
        cout << "\nМеню:\n";
        cout << "1. Статус героя\n";
        cout << "2. Осмотреться\n";
        cout << "3. Открыть книгу заклинаний\n";
        cout << "4. Использовать заклинание\n";
        cout << "0. Сохранить и выйти\n";
        cout << "Ваш выбор: ";
        break;
    case 2:
        cout << "Каким образом вы хотите инициализировать героя:\n";
        cout << "1. Вручную\n";
        cout << "2. Заранее подготовленный вариант\n";
        break;
    case 3:
        cout << "\nМеню заклинаний:\n";
        cout << "1. Добавить заклинание\n";
        cout << "2. Вывести заклинания\n";
        cout << "3. Обновить заклинание\n";
        cout << "4. Удалить заклинание\n";
        cout << "0. Выйти\n";
        break;
    case 4:
        cout << "\nМеню создания героя:\n";
        cout << "1. Добавить имя\n";
        cout << "2. Установить текущее колличество хп\n";
        cout << "3. Установить максимальное колличество хп\n";
        cout << "4. Установить колличество защиты\n";
        cout << "5. Установить сосредоточенность\n";
        cout << "0. Выйти\n";
        break;
    }
}



string elementToString(Element el) {
    using enum Element;
    switch (el) {
        
    case Fire: return "Огонь";
    case Earth: return "Земля";
    case Water: return "Вода";
    case Air: return "Воздух";
    case Spirit: return "Дух";
    default: return "Неизвестная стихия";
    }
}

Element selectElement() {
    int choice;
    cout << "Выберите стихию:\n";
    cout << "0 - Огонь\n";
    cout << "1 - Земля\n";
    cout << "2 - Вода\n";
    cout << "3 - Воздух\n";
    cout << "4 - Дух\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    

    return Element(choice);
}

//bool loadHero