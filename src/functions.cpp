#include "functions.h"
#include <conio.h>

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

void check() {
    char key;
    
    std::cout << "��������� �������. ��� ������ ������� 'q'.\n";

    while (true) {
        if (_kbhit()) {  // ���������, ���� �� ������ �������
            key = _getch();  // �������� ������ ������� �������

            switch (key) {
            case 'a':
                std::cout << "�� ������ 'a'. ����������� �������� A.\n";
                break;
            case 'b':
                std::cout << "�� ������ 'b'. ����������� �������� B.\n";
                break;
            case 'q':
                std::cout << "�� ������ 'q'. ����� �� ���������.\n";
                return;
            default:
                std::cout << "������ �������: " << key << "\n";
                break;
            }
        }
    }
}