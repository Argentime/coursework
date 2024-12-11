#include "header/EventSystem.h"
#include <iostream>

void EventSystem::registerEvent(const std::string& eventName, std::function<void()> handler) {
    events[eventName] = handler; // ����������� ����������� �������
}

void EventSystem::triggerEvent(const std::string& eventName) {
    if (events.find(eventName) != events.end()) {
        std::cout << "�������: " << eventName << " ��������.\n";
        events[eventName](); // ����� �����������
    }
    else {
        std::cerr << "������: ������� " << eventName << " �� �������.\n";
    }
}
