#include <vector>
#include "TimeStamp_Subject.hpp"

void TimeStamp_Subject::AddObserver(IObserver<float>* observer) 
{
    observers.push_back(observer);
}

void TimeStamp_Subject::RemoveObserver(IObserver<float>* observer)
{
    for(int i=0; i < observers.size(); i++)
    {
        if(observers[i] == observer)
        {
            observers.erase(observers.begin()+i);
            return;
        }
    }
}

int TimeStamp_Subject::GetObserversQuantity()
{
    return observers.size();
}

void TimeStamp_Subject::NotifyObservers() 
{
    float msg = GetMessage();

    for(int i=0; i < observers.size(); i++)
    {
        observers[i]->Update(msg);
    }
}