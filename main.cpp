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
#include "Schedulers/SJF.hpp"

#include <locale>

using namespace std;

vector<Process*> getProcess()
{
    vector<Process*> process;

    process.push_back(new Process(0, 20));
    process.push_back(new Process(0, 10));
    process.push_back(new Process(4, 6));
    process.push_back(new Process(4, 8));

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

    // for(int i = 0; i < process.size(); i++)
    //     cout << process[i]->ToString() << endl;

    ProcessSchedulerLog* log = new ProcessSchedulerLog(queue->Copy());
    cout << "FCFS " << log->ToString() << endl;
}

void testSJF()
{
    vector<Process*> process = getProcess();
    Queue<Process*>* queue = new Queue<Process*>();

    for(int i = 0; i < process.size(); i++)
    {
        queue->Enqueue(process[i]);
    }

    TimeStamp* timer = new TimeStamp();
    SJF* sjf = new SJF(timer, queue->Copy());

    while(sjf->IsProcessing())
    {
        timer->IncreaseTime(1);
    }

    // for(int i = 0; i < process.size(); i++)
    //     cout << process[i]->ToString() << endl;

    ProcessSchedulerLog* log = new ProcessSchedulerLog(queue->Copy());
    cout << "SJF " << log->ToString() << endl;
}

void testRR()
{
    vector<Process*> allProcesses = getProcess();
    Queue<Process*>* queue = QueueUtils::from_std_vector(allProcesses);

    TimeStamp* timer = new TimeStamp();
    RR* rr = new RR(timer, queue->Copy());

    while(rr->IsProcessing())
    {
        timer->IncreaseTime(1);
    }

    ProcessSchedulerLog* log = new ProcessSchedulerLog(queue->Copy());
    cout << "RR " << log->ToString() << endl;
}

int main()
{
    testFCFS();
    testSJF();
    testRR();
    
    return 0;
}