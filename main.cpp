#include <iostream>
#include <string>
#include <vector>
#include "Queue/Queue.hpp"
#include "Process/Process.hpp"
#include "Process/ProcessSchedulerLog.hpp"
#include "TimeStamp/TimeStamp.hpp"
#include "TimeStamp/TimeStamp_Observer.hpp"
#include "Schedulers/FCFS.hpp"
#include "Schedulers/RR.hpp"

using namespace std;

vector<Process*> getProcess()
{
    vector<Process*> process;

    process.push_back(new Process(0, 20));
    process.push_back(new Process(0, 10));
    process.push_back(new Process(4, 6));
    process.push_back(new Process(4, 8));

    // process.push_back(new Process(0, 24));
    // process.push_back(new Process(0, 3));
    // process.push_back(new Process(0, 3));

    return process;
}

void testFCFS()
{
    vector<Process*> process = getProcess();
    Queue<Process*>* queue = new Queue<Process*>();

    for(int i = 0; i < process.size(); i++)
    {
        queue->Enqueue(process[i]);
    }

    TimeStamp* timer = new TimeStamp();
    FCFS* fcfs = new FCFS(timer, queue->Copy());

    while(fcfs->IsProcessing())
        timer->IncreaseTime(1);

    for(int i = 0; i < process.size(); i++)
        cout << process[i]->ToString() << endl;

    ProcessSchedulerLog* log = new ProcessSchedulerLog(queue->Copy());
    cout << log->ToString() << endl;
}

void testRR()
{
    vector<Process*> process = getProcess();
    Queue<Process*>* queue = new Queue<Process*>();

    for(int i = 0; i < process.size(); i++)
    {
        queue->Enqueue(process[i]);
    }

    TimeStamp* timer = new TimeStamp();
    RR* rr = new RR(timer, queue->Copy());

    while(rr->IsProcessing())
    {
        timer->IncreaseTime(1);
    }

    for(int i = 0; i < process.size(); i++)
        cout << process[i]->ToString() << endl;

    ProcessSchedulerLog* log = new ProcessSchedulerLog(queue->Copy());
    cout << log->ToString() << endl;
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

void TestQueueCopy()
{
    Queue<int>* q1 = new Queue<int>();

    for(int i = 0; i < 10; i++)
        q1->Enqueue(i);
    
    Queue<int>* q2 = q1->Copy();

    for(int i = 0; i < 10; i++)
        q1->Dequeue();

    q2->Enqueue(-55);
    for(int i = 0; i < 11; i++)
        cout << q2->Dequeue() << " ";
}

#include <algorithm>
#include <functional>
#include "Queue/QueueUtils.hpp"
bool myfunction (Process* i, Process* j) { return (i->GetDurationLeft()<j->GetDurationLeft()); }

Queue<Process*>* sortQueue(Queue<Process*>* queue, function<bool(Process*, Process*)> func)
{
    vector<Process*> _vector = QueueUtils::to_std_vector(queue);
    std::sort(_vector.begin(), _vector.end(), func);   
    return QueueUtils::from_std_vector(_vector);
}

void TestQueueSort()
{
    Queue<Process*>* queue = new Queue<Process*>();
    queue->Enqueue(new Process(0, 1));
    queue->Enqueue(new Process(0, 11));
    queue->Enqueue(new Process(0, 3));
    queue->Enqueue(new Process(0, 15));
    queue->Enqueue(new Process(0, 25));
    queue->Enqueue(new Process(0, 47));

    queue = QueueUtils::sort_queue(queue, myfunction);// sortQueue(queue, myfunction);

    Process* p = queue->Dequeue();
    while(p != nullptr)
    {
        cout << "Valor: " << p->GetDurationLeft() << endl;
        p = queue->Dequeue();
    }
}

void sortVector()
{
    Queue<Process*>* queue = new Queue<Process*>();
    queue->Enqueue(new Process(0, 1));
    queue->Enqueue(new Process(0, 11));
    queue->Enqueue(new Process(0, 3));
    queue->Enqueue(new Process(0, 15));
    queue->Enqueue(new Process(0, 25));
    queue->Enqueue(new Process(0, 47));

    vector<Process*> process = QueueUtils::to_std_vector(queue); //getProcess();

    for(int i = 0; i < process.size(); i++)
        cout << process[i]->GetDurationLeft() <<" ";
    cout << endl;

    std::sort(process.begin(), process.end(), myfunction);   

    for(int i = 0; i < process.size(); i++)
        cout << process[i]->GetDurationLeft() <<" ";
    cout << endl;

    for(int i = 0; i < process.size(); i++)
        cout << process[i]->GetDurationLeft() <<  " ";
    cout << endl;
    cout << queue->Length() << " " << process.size() << "\n";

    queue = QueueUtils::from_std_vector(process);

    cout << queue->Length() << " " << process.size() << "\n";

    // for(int i = 0; i < queue->Length(); i++)
    //     cout << queue->Dequeue()->GetDurationLeft() << endl;
}

int main()
{
    //TestQueueCopy();
    //testFCFS();
    //testRR();
    //testObservers();

    //sortVector();
    TestQueueSort();
    return 0;
}