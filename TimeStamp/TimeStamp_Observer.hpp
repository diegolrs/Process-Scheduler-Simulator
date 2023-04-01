#pragma once
#include "../Observer/ObserverInterfaces.hpp"
#include "TimeStamp.hpp"

class TimeStamp_Observer : public IObserver<float>
{
    public:
        TimeStamp_Observer(TimeStamp* sender);
        ~TimeStamp_Observer();
        void Update(float message) override;
        void UnsubscribeFromEvent();
    protected:
        TimeStamp* sender;
    private:
        void SubscribeToEvent();
};