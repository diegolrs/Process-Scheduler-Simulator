#include "TimeStamp_Observer.hpp"
#include <iostream>

TimeStamp_Observer::TimeStamp_Observer(TimeStamp* sender)
{
    this->sender = sender;
    SubscribeToEvent();
}

TimeStamp_Observer::~TimeStamp_Observer()
{
    UnsubscribeFromEvent();
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