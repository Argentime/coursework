#include "header/StoryManager.h"
#include <qdebug.h>

StoryManager::StoryManager()=default;

void StoryManager::addStage(std::shared_ptr<StoryStage> stage) {
    stages.push_back(stage);
}


void StoryManager::startNextStage() {
    if (currentStageIndex + 1 < stages.size()) {
        currentStageIndex++;
        stages[currentStageIndex]->start();
    }
    else {
        qInfo() << "No more stages!";
    }
}

void StoryManager::completeCurrentStage() {
    if (currentStageIndex >= 0 && currentStageIndex < stages.size()) {
        stages[currentStageIndex]->complete();
    }
}


bool StoryManager::isStoryFinished() const {
    return currentStageIndex >= stages.size() - 1;
}

std::shared_ptr<StoryStage> StoryManager::getCurrentStage() const {
    if (currentStageIndex >= 0 && currentStageIndex < stages.size()) {
        return stages[currentStageIndex];
    }
    return nullptr;
}

void StoryManager::startStage(int index) {
    if (index >= 0 && index < stages.size()) {
        currentStageIndex = index;
        stages[currentStageIndex]->start();
    }
    else {
        qInfo() << "Invalid stage index!";
    }
}

std::shared_ptr<StoryStage> StoryManager::getStage(int index) const {
    if (index >= 0 && index < stages.size()) {
        return stages[index];
    }
    return nullptr;
}



void StoryManager::restartStage(const std::string& stageName) {
    for (size_t i = 0; i < stages.size(); ++i) {
        if (stages[i]->getDescription() == stageName) {
            currentStageIndex = i;
            stages[i]->start();
            return;
        }
    }

    qInfo() << "Stage with name" << QString::fromStdString(stageName) << "not found!";
}