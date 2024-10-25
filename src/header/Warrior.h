#pragma once
class Hero;
class Spell;

template<typename T, typename U>
class Warrior {
public:
    // ��������� ����� attack, ����������� ������ ���� T
    virtual void attack(T& another, U& spell) = 0; // ����������� �����
     virtual void disperseFocus(Hero& another, int impact) = 0;
    // ����������� ���������� ��� ����������� �������� ����� ��������� �� ������� �����
    virtual ~Warrior() = default;
};