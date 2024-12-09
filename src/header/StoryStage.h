#pragma once
#include <string>
#include <functional>

class StoryStage {
private:
    std::string description;              // �������� �����
    std::function<void()> onStart;        // �������� ��� ������ �����
    std::function<void()> onComplete;     // �������� ��� ����������
    bool isCompleted = false;

public:
    StoryStage(const std::string& desc, std::function<void()> start, std::function<void()> complete);

    void start();
    void complete();
    bool completed() const;
    std::string getDescription() const;
};
