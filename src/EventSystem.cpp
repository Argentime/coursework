#include "header/EventSystem.h"
#include <iostream>

void EventSystem::registerEvent(const std::string& eventName, std::function<void()> handler) {
    events[eventName] = handler; // Регистрация обработчика события
}

void EventSystem::triggerEvent(const std::string& eventName) {
    if (events.find(eventName) != events.end()) {
        std::cout << "Событие: " << eventName << " запущено.\n";
        events[eventName](); // Вызов обработчика
    }
    else {
        std::cerr << "Ошибка: событие " << eventName << " не найдено.\n";
    }
}
