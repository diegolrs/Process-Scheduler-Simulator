#include <iostream>
#include <string>
#include <vector>
#include "Queue/Queue.hpp"
#include "Process/Process.hpp"
#include "TimeStamp/TimeStamp.hpp"
#include "TimeStamp/TimeStamp_Observer.hpp"

using namespace std;

vector<Process> getProcess()
{
    vector<Process> process;

    process.push_back(Process(0, 20));
    process.push_back(Process(0, 10));
    process.push_back(Process(4, 6));
    process.push_back(Process(4, 8));

    return process;
}

void testQueueIteration()
{
    Queue<int>* q = new Queue<int>();

    for(int i = 0; i < 10; i++)
    {
        q->Enqueue(i);
        cout << i << " ";
    }
    cout << endl;

    int length = q->Length();

    // iterar fila e aplicar tempo
    for(int i = 0; i < length; i++)
    {
        int p = q->Dequeue();
        p *= 2;
        q->Enqueue(p);
    }

    length = q->Length();
    for(int i = 0; i < length; i++)
    {
        cout << q->Dequeue() << " ";
    }
}

void testObservers()
{
    TimeStamp* sender = new TimeStamp();

    for(int i = 0; i < 4; i++)
    {
        TimeStamp_Observer* observer = new TimeStamp_Observer(sender);

        if(i%2==0)
            delete observer;//->UnsubscribeFromEvent();
    }

    for(int i = 0; i < 5; i++)
    {
        sender->IncreaseTime(1);
    }
}

int main()
{
    testObservers();
    return 0;
}