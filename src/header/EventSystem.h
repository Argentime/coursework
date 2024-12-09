#pragma once
#include <functional>
#include <unordered_map>
#include <string>

class EventSystem {
private:
    std::unordered_map<std::string, std::function<void()>> events;

public:
    void registerEvent(const std::string& eventName, std::function<void()> handler);
    void triggerEvent(const std::string& eventName);
};
