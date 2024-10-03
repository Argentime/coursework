#include "header/Spell.h"

using namespace std;

Spell::Spell(string const& n, Element el1, Element el2, int dmg)
        : name(n), element1(el1), element2(el2), damage(dmg) {}

void Spell::display() const {
    cout << name
        << ": " << elementToString(element1)
        << " + " << elementToString(element2)
        << ", ����: " << damage << endl;
}

void Spell::useSpell() {
    uses++;
    cout << "���������� " << name << " ������� ���������\n";
    evolve();
}

void Spell::evolve() {
    if (uses % 2 == 0) {
        damage += 5;
        cout << "���������� " << name
            << " ����������������, ����� ����: "
            << damage << endl;
    }
}