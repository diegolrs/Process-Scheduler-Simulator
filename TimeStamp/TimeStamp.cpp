#include "TimeStamp.hpp"

TimeStamp::TimeStamp()
{
    time = 0;
}   

void TimeStamp::IncreaseTime(float delta)
{
    time += delta;
    this->NotifyObservers();
}

float TimeStamp::GetTime()
{
    return time;
}

float TimeStamp::GetMessage()
{
    return time;
}