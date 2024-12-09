#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "StoryStage.h"

class StoryManager {
private:
    std::vector<std::shared_ptr<StoryStage>> stages; // Список этапов сюжета
    int currentStageIndex = 0;

public:
    StoryManager();

    void addStage(std::shared_ptr<StoryStage> stage);
    void startNextStage();
    void completeCurrentStage();
    bool isStoryFinished() const;
    std::shared_ptr<StoryStage> getCurrentStage() const;
};
