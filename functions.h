#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

enum Element {
    Fire,   // �����
    Earth,  // �����
    Water,  // ����
    Air,    // ������
    Spirit  // ���
};

void printMenu();
string elementToString(Element el);
Element selectElement();