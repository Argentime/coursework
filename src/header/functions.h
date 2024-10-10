#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>

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



void printMenu(int var);
std::string elementToString(Element el);
Element selectElement();

std::string utf8ToWin1251(const std::string& utf8Str);

std::string win1251ToUtf8(const std::string& win1251Str);

#include "lib/nlohmann/json.hpp"
#include "header/Spell.h"
#include "header/SpellBook.h"
#include "header/Character.h"
#include "header/Warrior.h"
#include "header/Hero.h"
using nlohmann::json;

json serializeSpell(const Spell& spell);

Spell deserializeSpell(const json& j);

void saveHeroToJson(const Hero& hero, const std::string& filename);

void loadHeroFromJson(Hero& hero, const std::string& filename);

void manageSpellBook(SpellBook& mySpellBook);

void manageHero(Hero& hero);



