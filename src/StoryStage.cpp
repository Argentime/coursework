#include "header/StoryStage.h"
#include <iostream>

StoryStage::StoryStage(const std::string& desc, std::function<void()> start, std::function<void()> complete)
    : description(desc), onStart(start), onComplete(complete) {}

void StoryStage::addAction(const std::string& actionText, std::function<void()> action) {
    actions.emplace_back(actionText, action);
}

void StoryStage::start() {
    if (onStart) onStart();
}

const std::vector<std::pair<std::string, std::function<void()>>>& StoryStage::getActions() const {
    return actions;
}

void StoryStage::complete() {
    if (onComplete) onComplete();
}


std::string StoryStage::getDescription() const {
    return description;
}

