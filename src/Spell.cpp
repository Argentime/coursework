#include "header/Spell.h"

using namespace std;

Spell::Spell(string const& n, Element el1, Element el2, int dmg)
        : name(n), element1(el1), element2(el2), damage(dmg) {}

Spell::Spell(const Spell& other) {
    if (this != &other) {
        name = other.name;
        element1 = other.element1;
        element2 = other.element2;
        damage = other.damage;
        uses = other.uses;
    }
}

Spell& Spell::operator=(const Spell& other) {
	if (this != &other) {
		name = other.name;
		element1 = other.element1;
		element2 = other.element2;
		damage = other.damage;
		uses = other.uses;
	}
	return *this;
}

void Spell::display() const {
    cout << name
        << ": " << elementToString(element1)
        << " + " << elementToString(element2)
        << ", Урон: " << damage << endl;
}

void Spell::useSpell() {
    uses++;
    cout << "Заклинание " << name << " успешно применено\n";
    evolve();
}

void Spell::evolve() {
    if (uses % 2 == 0) {
        damage += 5;
        cout << "Заклинание " << name
            << " эволюционировало, новый урон: "
            << damage << endl;
    }
}