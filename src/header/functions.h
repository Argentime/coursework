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

std::string utf8ToWin1251(const std::string& utf8Str);

std::string win1251ToUtf8(const std::string& win1251Str);

#include "header/nlohmann/json.hpp"
#include "header/Spell.h"
#include "header/SpellBook.h"
#include <fstream>
using json = nlohmann::json;

json serializeSpell(const Spell& spell);

Spell deserializeSpell(const json& j);

void saveSpellBookToJson(const SpellBook& spellBook, const std::string& filename);

void loadSpellBookFromJson(SpellBook& spellBook, const std::string& filename);




