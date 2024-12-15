#pragma once

#include <vector>
#include <memory>
#include "StoryStage.h"


class StoryManager {
private:
    std::vector<std::shared_ptr<StoryStage>> stages; 
    int currentStageIndex;  

public:
    StoryManager();

    void addStage(std::shared_ptr<StoryStage> stage);
    void startNextStage();
    void completeCurrentStage();
    bool isStoryFinished() const;

    std::shared_ptr<StoryStage> getCurrentStage() const;
    void restartStage(const std::string& stageName);

    void startStage(int index);      
    std::shared_ptr<StoryStage> getStage(int index) const; 
};