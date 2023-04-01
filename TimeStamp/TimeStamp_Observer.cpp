#include "TimeStamp_Observer.hpp"
#include <iostream>

TimeStamp_Observer::TimeStamp_Observer(TimeStamp_Subject* sender) : IObserver<float>(sender)
{
    SubscribeToEvent();
}

void TimeStamp_Observer::Update(float message)
{
    std::cout << "[RECEBIDO]: " << message << std::endl;
}

void TimeStamp_Observer::SubscribeToEvent()
{
    if(sender != nullptr)
        sender->AddObserver(this);
}

void TimeStamp_Observer::UnsubscribeFromEvent() 
{
    if(sender != nullptr)
        sender->RemoveObserver(this);
}