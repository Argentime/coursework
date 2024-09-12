#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

enum Element {
    Fire,   // Огонь
    Earth,  // Земля
    Water,  // Вода
    Air,    // Воздух
    Spirit  // Дух
};

void printMenu();
string elementToString(Element el);
Element selectElement();