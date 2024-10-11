#include "header/functions.h"
#include "header/Hero.h"

using namespace std;
using json = nlohmann::json;

int main() {

   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

   Hero hero("", 0, 0, 0);

    int choice;

     do{
        printMenu(2);
        cin >> choice;
        switch (choice) {
        case 1: {
            manageSpellBook(hero.getSpellBook());
            manageHero(hero);
            saveHeroToJson(hero, "resources/Save.json");
            break;
        }
        case 2: {
            loadHeroFromJson(hero, "resources/DefaultSave.json");
            break;
        }
        default: {
            cout << "Введите число 1 либо 2.\n";
        }
        }
     } while ((choice != 1) && (choice != 2));
    
     do {
         printMenu(1);
         cin >> choice;
         cout << endl;

         switch (choice) {
         case 1: {
             cout << hero;
             break;
         }
         case 2: {
             cout << "Функция в разработке"<<endl;
             break;
         }
         case 3: {
             cout << hero.getSpellBook();
             break;
         }
         case 4: {
             int numb;
             cout << "Введите номер заклинания: ";
             cin >> numb;
             hero.getSpellBook().getSpells()[numb-1]->useSpell();
             hero.attack(hero, hero.getSpellBook().getSpells()[numb - 1]->damage);
             hero.decreaseFocus(2);
             break;
         }
         case 0: {
             saveHeroToJson(hero, "resources/Save.json");
             cout << "Выход из программы" << endl;
             return 0;
         }
         default: {
             cout << "Выберите число от 0 до 4.\n";
         }
         }
     } while (choice);
}