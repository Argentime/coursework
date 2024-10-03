#include "header/functions.h"

using namespace std;

void printMenu() {
    cout << "\nМеню:\n";
    cout << "1. Добавить заклинание\n";
    cout << "2. Показать все заклинания\n";
    cout << "3. Обновить заклинание\n";
    cout << "4. Удалить заклинание\n";
    cout << "5. Использовать заклинание\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
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