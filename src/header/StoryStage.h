#pragma once
#include <string>
#include <functional>

class StoryStage {
private:
    std::string description;              // Описание этапа
    std::function<void()> onStart;        // Действия при старте этапа
    std::function<void()> onComplete;     // Действия при завершении
    bool isCompleted = false;

public:
    StoryStage(const std::string& desc, std::function<void()> start, std::function<void()> complete);

    void start();
    void complete();
    bool completed() const;
    std::string getDescription() const;
};
