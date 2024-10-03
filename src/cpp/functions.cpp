#include "header/functions.h"

using namespace std;

void printMenu() {
    cout << "\n����:\n";
    cout << "1. �������� ����������\n";
    cout << "2. �������� ��� ����������\n";
    cout << "3. �������� ����������\n";
    cout << "4. ������� ����������\n";
    cout << "5. ������������ ����������\n";
    cout << "0. �����\n";
    cout << "��� �����: ";
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