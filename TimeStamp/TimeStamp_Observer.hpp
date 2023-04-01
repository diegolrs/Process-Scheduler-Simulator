#pragma once
#include "../Observer/ObserverInterfaces.hpp"
#include "TimeStamp_Subject.hpp"

class TimeStamp_Observer : public IObserver<float>
{
    public:
        TimeStamp_Observer(TimeStamp_Subject* sender);
        void Update(float message) override;
        void UnsubscribeFromEvent();
    private:
        void SubscribeToEvent();
};