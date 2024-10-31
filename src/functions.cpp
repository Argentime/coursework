#include "header/functions.h"
#include "header/SecondWindow.h"

using namespace std;
using json = nlohmann::json;

template <typename SpellType>
json serializeSpell(const SpellType& spell) {
    return json{
        {"name", spell.name},
        {"element1", spell.element1},
        {"element2", spell.element2},
        {"damage", spell.damage},
        {"uses", spell.uses}
    };
}
template <typename SpellType>
Spell deserializeSpell(const json& j) {
    string name = j.at("name").get<string>();
    auto el1 = static_cast<Element>(j.at("element1").get<int>());
    auto el2 = static_cast<Element>(j.at("element2").get<int>());
    int damage = j.at("damage").get<int>();
    int uses = j.at("uses").get<int>();

    SpellType spell(name, el1, el2, damage);
    spell.uses = uses;

    return spell;
}

bool operator==(HealthStats hp, int percent);

void printMenu(int var, QLabel* label) {

    switch (var) {
    case 1:
        label->setText(
"<body>Открыв глаза, вы медленно оглядываетесь вокруг. Вы находитесь в небольшой, тускло освещённой комнате. " 
"Вокруг царит странное ощущение спокойствия, но в воздухе витает нечто неуловимое, словно призрак недавнего события.<br>"
"На массивном дубовом столе перед вами лежит старая, потрёпанная временем книга. Её потускневшая обложка испещрена древними символами, "
"которые, кажется, мерцают в слабом свете лампы. Шелест пыли наполняет воздух, когда вы протягиваете руку к книге, но что - то останавливает вас.<br>"
"Справа от вас, у противоположной стены, стоит большое, антикварное зеркало с замысловатыми узорами на раме. Ваше отражение в нём кажется странно отдалённым," 
"словно время искажает его.Глядя в своё лицо, вы не можете отделаться от мысли, что за вами наблюдают.<br>"
"Тишина давит на уши, пока ваше сердце учащённо бьётся в груди. Что вы собираетесь делать?</body>"
        );
        break;
    case 2:
        label->setText(
            "<body>Вы медленно осматриваете небольшую, тускло освещённую комнату.В ней царит странная тишина, а воздух наполняет ощущение покоя, прерываемое лишь лёгким шёпотом пыли. <br>"
            "Перед вами на массивном дубовом столе лежит старая, потрёпанная книга с таинственными символами на обложке.Она кажется живой в мягком свете лампы. <br>"
            "Прямо напротив вас, у стены, стоит большое антикварное зеркало с замысловатыми узорами.Ваше отражение выглядит странно, будто за ним скрывается что - то незнакомое. <br>"
            "В комнате нет ничего, кроме книги и зеркала, и вы задумываетесь : что же делать дальше? < / body>"

        );
        break;
    case 3:
        label->setText(
            "<body>Вы медленно протягиваете руку к книге. Когда ваши пальцы касаются потускневшей обложки, она словно оживает.<br>"
            "Открывая её, вы видите страницы, полные таинственных заклинаний и древних символов. Каждое слово манит вас, обещая силу и знания, "
            "которые могут изменить ход вашей судьбы. Эта книга — ваш ключ к магии, и вы чувствуете, что её заклинания готовы быть использованными.</body>"
        );
        break;
    case 4:
        label->setText(
            "<body>Вы подходите к зеркалу, настороженно всматриваясь в своё отражение. Однако, как только взглянули на поверхность, "
            "вас охватывает чувство пустоты. Зеркало показывает лишь ваше обычное отражение, ничего необычного. Лишь слабый свет "
            "подсвечивает ваши черты, оставляя ощущение, что в комнате не хватает чего-то важного. Пожалуй, это всего лишь обманчивое спокойствие.</body>"
        );
        break;
    case 5:
        label->setText(
            "<body>Подходя к зеркалу, вы внимательно смотрите на своё отражение. Внезапно вас охватывает странное желание — "
            "желание открыть книгу, лежащую на столе. Кажется, что именно в ней скрыты ответы на все ваши вопросы. "
            "Взгляд на зеркало лишь подчеркивает это чувство: будто книга зовёт вас, манит к себе, обещая раскрыть тайны, "
            "заслуживающие внимания. Пора разобраться в том, что она хранит.</body>"
        );
        break;
    case 6:
        
        label->setText(
            "<body style='line-height: 0.5;'>"
            "Вы открываете книгу заклинаний и видите перед собой следующие заклинания :"
        );
        break;
    case 7:
        cout << "\nМеню создания героя:\n";
        cout << "1. Добавить имя\n";
        cout << "2. Установить текущее колличество хп\n";
        cout << "3. Установить максимальное колличество хп\n";
        cout << "4. Установить колличество защиты\n";
        cout << "5. Установить сосредоточенность\n";
        cout << "0. Выйти\n";
        break;
    }
}

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

Element selectElement() {
    int choice;
    cout << "Выберите стихию:\n";
    cout << "0 - Огонь\n";
    cout << "1 - Земля\n";
    cout << "2 - Вода\n";
    cout << "3 - Воздух\n";
    cout << "4 - Дух\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    

    return Element(choice);
}

string win1251ToUtf8(const string& win1251Str) {
    int wcharsCount = MultiByteToWideChar(1251, 0, win1251Str.c_str(), -1, nullptr, 0);
    auto wstr = new wchar_t[wcharsCount];
    MultiByteToWideChar(1251, 0, win1251Str.c_str(), -1, wstr, wcharsCount);

    int utf8CharCount = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    auto utf8Str = new char[utf8CharCount];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8Str, utf8CharCount, nullptr, nullptr);

    string result(utf8Str);
    delete[] wstr;
    delete[] utf8Str;
    return result;
}

string utf8ToWin1251(const string& utf8Str) {
    int wcharsCount = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
    auto wstr = new wchar_t[wcharsCount];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wstr, wcharsCount);

    int win1251CharCount = WideCharToMultiByte(1251, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    auto win1251Str = new char[win1251CharCount];
    WideCharToMultiByte(1251, 0, wstr, -1, win1251Str, win1251CharCount, nullptr, nullptr);

    string result(win1251Str);
    delete[] wstr;
    delete[] win1251Str;
    return result;
}

void saveHeroToJson(const Hero& hero, const std::string& filename) {

    json heroJson;

    heroJson["spells"] = json::array();
    heroJson["h_mana"] = json::array();
    heroJson["h_money"] = hero.getMoney();
    heroJson["h_name"] = hero.getName();
    heroJson["h_hp"] = hero.getHealth().health;
    heroJson["h_maxHp"] = hero.getHealth().maxHealth;
    heroJson["h_defence"] = hero.getHealth().defense;
    heroJson["h_focus"] = hero.getFocus();

    for (int i = 0; i < hero.getSpellBook().getSpellCount(); ++i) {
        heroJson["spells"].push_back(serializeSpell<Spell>(*hero.getSpellBook().getSpells()[i]));
    }

    for (int i = 0; i < 5; ++i) {
        heroJson["h_mana"].push_back(hero.getMana(Element(i)));
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << heroJson.dump(4);
        file.close();
    }
    else {
        std::cerr << "Error: Could not open file for writing." << std::endl;
    }
}

void loadHeroFromJson(Hero& hero, const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        json heroJson;
        file >> heroJson;
        file.close();

        HealthStats hp;
        
        hp.defense = heroJson.at("h_defence").get<float>();
        hp.health = heroJson.at("h_hp").get<int>();
        hp.maxHealth = heroJson.at("h_maxHp").get<int>();
        string name = heroJson.at("h_name").get<string>();
        int focus = heroJson.at("h_focus").get<int>();
        int money = heroJson.at("h_money").get<int>();
        auto mana = new int[static_cast<int>(Element::Spirit) + 1];
        

        for (int i = 0; i < 5; ++i) {
            mana[i] = heroJson.at("h_mana").at(i).get<int>();
        }

        Hero bufHero(name, hp, focus, money, mana);
        

        for (const auto& spellJson : heroJson.at("spells")) {
            Spell spell = deserializeSpell<Spell>(spellJson);
            bufHero.getSpellBook().addSpell(spell.name, spell.element1, spell.element2, spell.damage);
        }
        hero = bufHero;
    }
    else {
        std::cerr << "Error: Could not open file for reading." << std::endl;
    }
}

void activeButtonCSS(QPushButton* b) {
    b->setMaximumHeight(20);
    b->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    b->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(122, 122, 122, 0);"
        "border: none;"
        "border-radius: 3px;"
        "padding: 4px;"
        "font-weight: 600;"
        "text-align: left;"
        "color: white;"
        "}"
        "QPushButton:hover {"
        "background-color: rgba(161, 161, 161, 20);"
        "}"
        "QPushButton:pressed {"
        "background-color: rgba(161, 161, 161, 10);"
        "}"
    );
    b->setIcon(QIcon(":/rec/resources/background_images/pimp.png"));
}

void inactiveButtonCSS(QPushButton* b) {
    b->setText("");
    b->setMaximumHeight(0);
    b->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    b->setStyleSheet(
        "QPushButton{"
        "background-color: rgba(122, 122, 122, 0);"
        "border: none;"
        "border-radius: 3px;"
        "padding: 4px;"
        "font-weight: 600;"
        "text-align: left;"
        "color: white;"
        "}"
    );
    b->setIcon(QIcon());
}