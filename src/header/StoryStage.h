#pragma once
#include <string>
#include <functional>

class StoryStage {
private:
    std::string description;             
    std::function<void()> onStart;
    std::function<void()> onComplete;
    std::vector<std::pair<std::string, std::function<void()>>> actions;
    bool isCompleted = false;

public:
    StoryStage(const std::string& desc, std::function<void()> start, std::function<void()> complete);

    void addAction(const std::string& actionText, std::function<void()> action);
    const std::vector<std::pair<std::string, std::function<void()>>>& getActions() const;

    void start();
    void complete();
    std::string getDescription() const;
};
