#include "header/StoryManager.h"

StoryManager::StoryManager() = default;

void StoryManager::addStage(std::shared_ptr<StoryStage> stage) {
    stages.push_back(stage);
}

void StoryManager::startNextStage() {
    if (currentStageIndex < stages.size()) {
        stages[currentStageIndex]->start();
    }
}

void StoryManager::completeCurrentStage() {
    if (currentStageIndex < stages.size()) {
        stages[currentStageIndex]->complete();
        currentStageIndex++;
    }
}

bool StoryManager::isStoryFinished() const {
    return currentStageIndex >= stages.size();
}

std::shared_ptr<StoryStage> StoryManager::getCurrentStage() const {
    if (currentStageIndex < stages.size()) {
        return stages[currentStageIndex];
    }
    return nullptr;
}
