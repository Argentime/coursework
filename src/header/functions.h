#pragma once
#include <string>
#include <iostream>
#include <Windows.h>


enum class Element {
    Fire,   
    Earth,  
    Water,  
    Air,    
    Spirit  
};

struct HealthStats {
    int health;
    int maxHealth;
    float defense;
};

void printMenu(int var);
std::string elementToString(Element el);
Element selectElement();




