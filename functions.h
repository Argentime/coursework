#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

enum class Element {
    Fire,   
    Earth,  //r
    Water,   
    Air,    
    Spirit  
};

void printMenu();
std::string elementToString(Element el);
Element selectElement(); 