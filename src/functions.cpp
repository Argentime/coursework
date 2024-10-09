#include "header/functions.h"

#include <fstream>

using namespace std;
using json = nlohmann::json;

void printMenu(int var) {
    switch (var) {
    case 1:
        cout << "\n����:\n";
        cout << "1. ������ �����\n";
        cout << "2. �����������\n";
        cout << "3. ������� ����� ����������\n";
        cout << "4. ������������ ����������\n";
        cout << "0. ��������� � �����\n";
        cout << "��� �����: ";
        break;
    case 2:
        cout << "����� ������� �� ������ ���������������� �����:\n";
        cout << "1. �������\n";
        cout << "2. ������� �������������� �������\n";
        break;
    case 3:
        cout << "\n���� ����������:\n";
        cout << "1. �������� ����������\n";
        cout << "2. ������� ����������\n";
        cout << "3. �������� ����������\n";
        cout << "4. ������� ����������\n";
        cout << "0. �����\n";
        break;
    case 4:
        cout << "\n���� �������� �����:\n";
        cout << "1. �������� ���\n";
        cout << "2. ���������� ������� ����������� ��\n";
        cout << "3. ���������� ������������ ����������� ��\n";
        cout << "4. ���������� ����������� ������\n";
        cout << "5. ���������� �����������������\n";
        cout << "0. �����\n";
        break;
    }
}

string elementToString(Element el) {
    using enum Element;
    switch (el) {
        
    case Fire: return "�����";
    case Earth: return "�����";
    case Water: return "����";
    case Air: return "������";
    case Spirit: return "���";
    default: return "����������� ������";
    }
}

Element selectElement() {
    int choice;
    cout << "�������� ������:\n";
    cout << "0 - �����\n";
    cout << "1 - �����\n";
    cout << "2 - ����\n";
    cout << "3 - ������\n";
    cout << "4 - ���\n";
    cout << "��� �����: ";
    cin >> choice;
    

    return Element(choice);
}

string win1251ToUtf8(const string& win1251Str) {
    int wcharsCount = MultiByteToWideChar(1251, 0, win1251Str.c_str(), -1, nullptr, 0);
    wchar_t* wstr = new wchar_t[wcharsCount];
    MultiByteToWideChar(1251, 0, win1251Str.c_str(), -1, wstr, wcharsCount);

    int utf8CharCount = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    char* utf8Str = new char[utf8CharCount];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8Str, utf8CharCount, nullptr, nullptr);

    string result(utf8Str);
    delete[] wstr;
    delete[] utf8Str;
    return result;
}

string utf8ToWin1251(const string& utf8Str) {
    int wcharsCount = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
    wchar_t* wstr = new wchar_t[wcharsCount];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wstr, wcharsCount);

    int win1251CharCount = WideCharToMultiByte(1251, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    char* win1251Str = new char[win1251CharCount];
    WideCharToMultiByte(1251, 0, wstr, -1, win1251Str, win1251CharCount, nullptr, nullptr);

    string result(win1251Str);
    delete[] wstr;
    delete[] win1251Str;
    return result;
}

json serializeSpell(const Spell& spell) {
    return json{
        {"name", win1251ToUtf8(spell.name)},
        {"element1", spell.element1},
        {"element2", spell.element2},
        {"damage", spell.damage},
        {"uses", spell.uses}
    };
}

Spell deserializeSpell(const json& j) {
    string name = utf8ToWin1251(j.at("name").get<string>());
    Element el1 = static_cast<Element>(j.at("element1").get<int>());
    Element el2 = static_cast<Element>(j.at("element2").get<int>());
    int damage = j.at("damage").get<int>();
    int uses = j.at("uses").get<int>();

    Spell spell(name, el1, el2, damage);
    spell.uses = uses;

    return spell;
}

void saveSpellBookToJson(const SpellBook& spellBook, const std::string& filename) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    json spellBookJson;

    spellBookJson["spellCount"] = spellBook.getSpellCount();
    spellBookJson["spells"] = json::array();

    for (int i = 0; i < spellBook.getSpellCount(); ++i) {
        spellBookJson["spells"].push_back(serializeSpell(*spellBook.getSpells()[i]));
    }

    // ��������� JSON � ����
    std::ofstream file(filename);
    if (file.is_open()) {
        file << spellBookJson.dump(4); // 4 - ������� ��� ������� ��������������
        file.close();
    }
    else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}

void loadSpellBookFromJson(SpellBook& spellBook, const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        json spellBookJson;
        file >> spellBookJson;
        file.close();

        // ��������� ����������
        int spellCount = spellBookJson.at("spellCount").get<int>();

        for (const auto& spellJson : spellBookJson.at("spells")) {
            Spell spell = deserializeSpell(spellJson);
            spellBook.addSpell(spell.name, spell.element1, spell.element2, spell.damage);
        }
    }
    else {
        std::cerr << "Error: Could not open file for reading." << std::endl;
    }
}

//bool loadHero