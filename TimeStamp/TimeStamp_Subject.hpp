#pragma once
#include <vector>
#include "../Observer/ObserverInterfaces.hpp"

class TimeStamp_Subject : public ISubject<float>
{
    public:
        void AddObserver(IObserver<float>* observer) override;
        void RemoveObserver(IObserver<float>* observer) override;   
        int GetObserversQuantity() override;   
    protected:
        void NotifyObservers() override;
    private:
        std::vector<IObserver<float>*> observers;
};