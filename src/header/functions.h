#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <qlabel.h>
#include <qpushbutton.h>
#include <QFile>

class Hero;

enum class Element {
    Fire,   
    Earth,  
    Water,  
    Air,    
    Spirit,
    None
};

struct HealthStats {
    int health;
    int maxHealth;
    float defense;
    friend bool operator==(HealthStats hp, int percent);
};

std::string elementToString(Element el);

#include "../lib/nlohmann/json.hpp"
#include "Spell.h"
#include "SpellBook.h"
#include "Character.h"
#include "Hero.h"
#include "Enemy.h"
#include "Battle.h"
#include "Game.h"


using nlohmann::json;


json serializeSpell(const Spell& spell);
Spell deserializeSpell(const json& j);

void loadHeroSpellBookFromJson(const std::string& filename, SpellBook* spellBook);

void activeButtonCSS(QPushButton* b);

void inactiveButtonCSS(QPushButton* b);

void loadHtmlToLabel(QLabel* label, const QString& filePath);

