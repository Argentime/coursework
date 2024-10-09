#include "header/functions.h"
#include "header/Spell.h"
#include "header/SpellBook.h"
#include "header/Character.h"
#include "header/nlohmann/json.hpp"
#include <fstream>

using namespace std;
using json = nlohmann::json;

int main() {

   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

    SpellBook mySpellBook;
    Character hero("", 0, 0);
    int choice;

     do{
        printMenu(2);
        cin >> choice;
        switch (choice) {
        case 1: {
            manageSpellBook(mySpellBook);
            manageHero(hero);
            saveSpellBookToJson(hero,mySpellBook, "Save.json");
            cout << hero << endl;
            break;
        }
        case 2: {
            loadSpellBookFromJson(hero,mySpellBook, "DefaultSave.json");
            manageSpellBook(mySpellBook);
            cout << hero << endl;
            break;
        }
        default: {
            cout << "������� ����� 1 ���� 2.\n";
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
             cout << "������� � ����������"<<endl;
             break;
         }
         case 3: {
             cout << mySpellBook;
             break;
         }
         case 4: {
             int numb;
             cout << "������� ����� ����������: ";
             cin >> numb;
             mySpellBook.getSpells()[numb-1]->useSpell();
             break;
         }
         case 0: {
             cout << "����� �� ���������" << endl;
             return 0;
         }
         default: {
             cout << "�������� ����� �� 0 �� 4.\n";
         }
         }
     } while (choice);
}