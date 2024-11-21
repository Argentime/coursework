#pragma once
#include "functions.h"

class Enemy: public Character
{
private:
	SpellBook mySpellBook;
	int* mana;
public:
	Enemy(std::string const& name, int health, int focus);
	Enemy(const Enemy& other);
	std::string status() const override;
	~Enemy() override;
	
	void setMana(int element, int value);

	const SpellBook& getSpellBook() const;
	SpellBook& getSpellBook();
	int getMana(Element element) const;

	Enemy& operator=(const Enemy* other);

};

