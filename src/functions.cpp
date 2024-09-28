#include "functions.h"
#include <conio.h>

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

void check() {
    char key;
    
    std::cout << "Нажимайте клавиши. Для выхода нажмите 'q'.\n";

    while (true) {
        if (_kbhit()) {  // Проверяем, была ли нажата клавиша
            key = _getch();  // Получаем символ нажатой клавиши

            switch (key) {
            case 'a':
                std::cout << "Вы нажали 'a'. Выполняется действие A.\n";
                break;
            case 'b':
                std::cout << "Вы нажали 'b'. Выполняется действие B.\n";
                break;
            case 'q':
                std::cout << "Вы нажали 'q'. Выход из программы.\n";
                return;
            default:
                std::cout << "Нажата клавиша: " << key << "\n";
                break;
            }
        }
    }
}