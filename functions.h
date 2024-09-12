#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

enum class Element {
    Fire,   // Огонь
    Earth,  // Земля
    Water,  // Вода
    Air,    // Воздух
    Spirit  // Дух
};

void printMenu();
std::string elementToString(Element el);
Element selectElement();