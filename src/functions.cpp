#include "header/functions.h"
#include "header/SecondWindow.h"

using namespace std;
using json = nlohmann::json;

bool operator==(HealthStats hp, int percent) {
    int healthPercentage = (hp.maxHealth == 0) ? 0 : (hp.health * 100) / hp.maxHealth;
    return healthPercentage <= percent;
};


json serializeSpell(const Spell& spell) {
    return json{
        {"type", spell.type},
        {"name", spell.name},
        {"element1", spell.element1},
        {"element2", spell.element2},
        {"damage", spell.damage},
        {"uses", spell.uses}
    };
}


Spell deserializeSpell(const json& j) {
    
    auto el1 = static_cast<Element>(j.at("element1").get<int>());
    string name = j.at("name").get<string>();
    auto el2 = static_cast<Element>(j.at("element2").get<int>());
    int damage = j.at("damage").get<int>();
    int uses = j.at("uses").get<int>();
    SpellType type = static_cast<SpellType>(j.at("type").get<int>());

    Spell spell(name, el1, el2, damage, type);
    spell.uses = uses;

    return spell;
}

bool operator==(HealthStats hp, int percent);
string elementToString(Element el) {
    using enum Element;
    switch (el) {
        
    case Fire: return "Огонь";
    case Earth: return "Земля";
    case Water: return "Вода";
    case Air: return "Воздух";
    case Spirit: return "Дух";
    default: return "Неизвестная стихия";
    }
}

void loadHeroSpellBookFromJson(const std::string& filename, SpellBook* spellBook) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for reading.");
    }

    try {
        nlohmann::json heroJson;
        file >> heroJson;
        file.close();

        for (const auto& spellJson : heroJson.at("spells")) {
            Spell spell = deserializeSpell(spellJson);
            spellBook->addSpell(spell.name, spell.element1, spell.element2, spell.damage, spell.type);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading spell book: " << e.what() << std::endl;
    }
}

void activeButtonCSS(QPushButton* b) {
    b->setMaximumHeight(20);
    b->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    b->setEnabled(true);
    b->setIcon(QIcon(":/rec/resources/background_images/pimp.png"));
}

void inactiveButtonCSS(QPushButton* b) {
    b->setText("");
    b->setMaximumHeight(0);
    b->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    b->setEnabled(false);
    b->setIcon(QIcon());
}

void loadHtmlToLabel(QLabel* label, const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Failed to load file: " + filePath);
        return;
    }

    QTextStream stream(&file);
    label->setText(stream.readAll());
    file.close();
}

