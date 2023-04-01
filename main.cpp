#include <iostream>
#include <string>
#include "Queue/Queue.hpp"
#include "Process/Process.hpp"
#include "TimeStamp/TimeStamp.hpp"
#include "TimeStamp/TimeStamp_Observer.hpp"

using namespace std;

int main()
{
    TimeStamp* sender = new TimeStamp();

    for(int i = 0; i < 8; i++)
    {
        TimeStamp_Observer* observer = new TimeStamp_Observer(sender);

        if(i%2==0)
            observer->UnsubscribeFromEvent();
    }

    for(int i = 0; i < 5; i++)
    {
        sender->IncreaseTime(1);
    }

    cout << "main";
    return 0;
}