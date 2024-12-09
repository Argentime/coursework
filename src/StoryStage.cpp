#include "header/StoryStage.h"
#include <iostream>

StoryStage::StoryStage(const std::string& desc, std::function<void()> start, std::function<void()> complete)
    : description(desc), onStart(start), onComplete(complete) {}

void StoryStage::start() {
    if (onStart) {
        std::cout << "Начало этапа: " << description << "\n";
        onStart();
    }
}

void StoryStage::complete() {
    if (onComplete) {
        onComplete();
    }
    isCompleted = true;
}

bool StoryStage::completed() const {
    return isCompleted;
}

std::string StoryStage::getDescription() const {
    return description;
}
