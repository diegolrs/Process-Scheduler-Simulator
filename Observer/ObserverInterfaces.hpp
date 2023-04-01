#pragma once

template <typename T>
class ISubject;

template <typename T>
class IObserver 
{
    public:
        virtual void Update(T message) = 0;
};

template <typename T>
class ISubject 
{
    public:
        virtual void AddObserver(IObserver<T> *observer) = 0;
        virtual void RemoveObserver(IObserver<T> *observer) = 0;
        virtual int GetObserversQuantity() = 0;
    protected:
        virtual T GetMessage() = 0;
        virtual void NotifyObservers() = 0;
};