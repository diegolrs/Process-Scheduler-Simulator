#include "TimeStamp.hpp"

TimeStamp::TimeStamp()
{
    time = 0;
}   

float TimeStamp::GetTotalTime()
{
    return time;
}

void TimeStamp::IncreaseTime(float delta)
{
    time += delta;
    lastTimeIncreased = delta;
    this->NotifyObservers();
}

// Returns last delta time increased
float TimeStamp::GetMessage()
{
    return lastTimeIncreased;
}