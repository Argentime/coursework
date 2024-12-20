﻿#pragma once
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
    friend bool operator==(HealthStats hp, int percent) {
        int healthPercentage = (hp.maxHealth==0) ? 0 : (hp.health*100) / hp.maxHealth;
        return healthPercentage <= percent;
    };
};

std::string elementToString(Element el);
Element selectElement();

std::string utf8ToWin1251(const std::string& utf8Str);

std::string win1251ToUtf8(const std::string& win1251Str);

#include "../lib/nlohmann/json.hpp"
#include "Spell.h"
#include "SpellBook.h"
#include "Character.h"
#include "Warrior.h"
#include "Hero.h"


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



