#pragma once
#include "TimeStamp_Subject.hpp"

class TimeStamp : public TimeStamp_Subject
{
    public:
        TimeStamp();
        void IncreaseTime(float delta);
        float GetTotalTime();
        float GetMessage() override; // To Observers
    private:
        float time;
        float lastTimeIncreased;
};