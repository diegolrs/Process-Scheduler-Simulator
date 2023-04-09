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
#include "Process/Process_FileReader.hpp"

using namespace std;

vector<Process*> readDataFromFile()
{
    return Process_FileReader::ReadFile("input.txt");
}

Queue<Process*>* clone_vector_and_items_to_queue(std::vector<Process*> original)
{
    Queue<Process*>* clone = new Queue<Process*>();

    for(int i = 0; i < original.size(); i++)
    {
        Process* _ = new Process();
        _->SetEnteringTime(original[i]->GetEnteringTime());
        _->SetDurationTime(original[i]->GetDurationTime());
        clone->Enqueue(_);
    }

    return clone;
}

void executeSchedulers(std::vector<Process*> allProcesses)
{
    TimeStamp* timer = new TimeStamp();

    Queue<Process*>* queueFCFS = clone_vector_and_items_to_queue(allProcesses);
    Queue<Process*>* queueSJF = clone_vector_and_items_to_queue(allProcesses);
    Queue<Process*>* queueRR = clone_vector_and_items_to_queue(allProcesses);
    
    FCFS* fcfs = new FCFS(timer, queueFCFS);
    SJF* sjf = new SJF(timer, queueSJF);
    RR* rr = new RR(timer, queueRR);

    while(fcfs->IsProcessing() || sjf->IsProcessing() || rr->IsProcessing())
    {
        timer->IncreaseTime(1);
    }

    ProcessSchedulerLog* FCFSlog = new ProcessSchedulerLog(queueFCFS);
    ProcessSchedulerLog* SJFlog = new ProcessSchedulerLog(queueSJF);
    ProcessSchedulerLog* RRlog = new ProcessSchedulerLog(queueRR);

    cout << "FCFS " << FCFSlog->ToString() << endl;
    cout << "SJF " << SJFlog->ToString() << endl;
    cout << "RR " << RRlog->ToString() << endl;
}

int main()
{
    vector<Process*> allProcesses = readDataFromFile();
    executeSchedulers(allProcesses);
    return 0;
}