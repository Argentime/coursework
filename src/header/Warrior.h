#pragma once
class Hero;
class Spell;

template<typename T, typename U>
class Warrior {
public:
    // Шаблонный метод attack, принимающий объект типа T
    virtual void attack(T& another, U& spell) = 0; // Абстрактный метод
     virtual void disperseFocus(Hero& another, int impact) = 0;
    // Виртуальный деструктор для корректного удаления через указатель на базовый класс
    virtual ~Warrior() = default;
};