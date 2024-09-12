#include "functions.h"

using namespace std;

void printMenu() {
    cout << "\n����:\n";
    cout << "1. �������� ����������\n";
    cout << "2. �������� ��� ����������\n";
    cout << "3. �������� ����������\n";
    cout << "4. ������� ����������\n";
    cout << "0. �����\n";
    cout << "��� �����: ";
}

string elementToString(Element el) {
    switch (el) {
    case Element::Fire: return "�����";
    case Element::Earth: return "�����";
    case Element::Water: return "����";
    case Element::Air: return "������";
    case Element::Spirit: return "���";
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

    return static_cast<Element>(choice);
}