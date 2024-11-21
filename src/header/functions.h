#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <qlabel.h>
#include <qpushbutton.h>

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
    friend bool operator==(HealthStats hp, int percent);
};

std::string elementToString(Element el);
Element selectElement();

#include "../lib/nlohmann/json.hpp"
#include "Spell.h"
#include "SpellBook.h"
#include "Character.h"
#include "Hero.h"
#include "Enemy.h"
#include "Battle.h"
#include "Game.h"


using nlohmann::json;

template <typename SpellType> 
json serializeSpell(const SpellType& spell);

template <typename SpellType>
Spell deserializeSpell(const json& j);

void saveHeroToJson(const Hero& hero, const std::string& filename);

void loadHeroFromJson(Hero& hero, const std::string& filename);

void printMenu(int var, QLabel* label);

void activeButtonCSS(QPushButton* b);

void inactiveButtonCSS(QPushButton* b);



