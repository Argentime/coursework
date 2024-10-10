#include "header/Hero.h"
#include "header/functions.h"
#include "header/Warrior.h"

using namespace std;

Hero::Hero(string const& name, int health, int focus, int money)
    : Character(name, health, focus), money(money) {
    mana = new int[static_cast<int>(Element::Spirit) + 1];
    for (int i = 0; i < 5; ++i) {
        mana[i] = 100;
    }
}

Hero::Hero(string const& name, HealthStats newHealth, int focus, int money, int *mana)
    : Character(name, newHealth, focus), money(money), mana(mana) {}

Hero::Hero(const Hero& other)
    : Character(other.getName(), other.getHealth(), other.getFocus()),
    money(other.getMoney()),
    mySpellBook(other.getSpellBook()),
    mana(new int[static_cast<int>(Element::Spirit)+1])
{
    for (int i = 0; i <= static_cast<int>(Element::Spirit); i++) {
        mana[i] = other.getMana(Element(i));
    }
}

Hero::~Hero() {
    delete[] mana;
}

Hero& Hero::operator=(const Hero& another) {
    name = another.getName();
    hp = another.getHealth();
    focus = another.getFocus();
    money = another.getMoney();
    for (int i = 0; i <= static_cast<int>(Element::Spirit); i++) {
        mana[i] = another.getMana(Element(i));
    }
    mySpellBook = another.getSpellBook();
    return *this;
}

ostream& operator<<(ostream& os, const Hero& hero) {
    using enum Element;
    
    os << "���: " << hero.getName() << endl;
    os << "���������: " << hero.status() << endl;
    os << "�����������������: " << hero.getFocus() << endl;
    os << "����: " << endl;
    os << "�����: " << hero.getMana(Fire) << endl;
    os << "�����: " << hero.getMana(Earth) << endl;
    os << "����: " << hero.getMana(Water) << endl;
    os << "������: " << hero.getMana(Air) << endl;
    os << "���: " << hero.getMana(Spirit) << endl;
    return os;
}

// ������ � ������ ��� �����
int Hero::getMoney() const {
    return money;
}

void Hero::setMoney(int newMoney) {
    money = newMoney;
}

// ������ � ������ ��� ����
int Hero::getMana(Element el) const {
    using enum Element;
    switch (el) {
    
    case Fire: return mana[0];
    case Earth: return mana[1];
    case Water: return mana[2];
    case Air: return mana[3];
    case Spirit: return mana[4];
    default: return 0;
    }
}

void Hero::setMana(int element, int value) {
    if (element >= 0 && element < 5) {
        mana[element] = value;
    }
}

// ������ � ������ ����������
const SpellBook& Hero::getSpellBook() const {
    return mySpellBook;
}

SpellBook& Hero::getSpellBook() {
    return mySpellBook;
}

// ��������������� ������ status() �� ������ Character
std::string Hero::status() const {
    if (hp == Stats.VeryWeak) {
        return "�� ���������";
    }
    else if (hp == Stats.Weak) {
        return "�� ��� ������ �� �����";
    }
    else if (hp == Stats.Normal) {
        return "��� ������� ������";
    }
    else if (hp == Stats.Strong) {
        return "�� ���������� ���� �������";
    }
    else {
        return "�� ����� ���!";
    }
}

// ��������������� ������ ����� �� ������ Warrior
void Hero::attack(Hero& another, int damage) {
    another.takeDamage(damage);
}

void Hero::disperseFocus(Hero& another, int impact) {
    another.decreaseFocus(impact);
}
