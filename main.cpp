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

void testFCFS(std::vector<Process*> allProcesses)
{
    Queue<Process*>* queue = QueueUtils::from_std_vector(allProcesses);

    TimeStamp* timer = new TimeStamp();
    FCFS* fcfs = new FCFS(timer, queue->Copy());

    while(fcfs->IsProcessing())
        timer->IncreaseTime(1);

    ProcessSchedulerLog* log = new ProcessSchedulerLog(queue->Copy());
    cout << "FCFS " << log->ToString() << endl;
}

void testSJF(std::vector<Process*> allProcesses)
{
    Queue<Process*>* queue = QueueUtils::from_std_vector(allProcesses);

    TimeStamp* timer = new TimeStamp();
    SJF* sjf = new SJF(timer, queue->Copy());
    while(sjf->IsProcessing())
    {
        timer->IncreaseTime(1);
    }

    ProcessSchedulerLog* log = new ProcessSchedulerLog(queue->Copy());
    cout << "SJF " << log->ToString() << endl;
}

void testRR(std::vector<Process*>  allProcesses)
{
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

std::vector<Process*> clone_vector_and_items(std::vector<Process*> original)
{
    std::vector<Process*> clone;

    for(int i = 0; i < original.size(); i++)
    {
        Process* _ = new Process();
        _->SetEnteringTime(original[i]->GetEnteringTime());
        _->SetDurationTime(original[i]->GetDurationTime());
        clone.push_back(_);
    }

    return clone;
}

// TODO: Fix this function
void process(std::vector<Process*> allProcesses)
{
    std::vector<Process*> list = clone_vector_and_items(allProcesses);
    Queue<Process*>* queue = QueueUtils::from_std_vector(allProcesses);
    
    TimeStamp* timer = new TimeStamp();
    FCFS* fcfs = new FCFS(timer, queue->Copy());
    SJF* sjf = new SJF(timer, queue->Copy());
    RR* rr = new RR(timer, queue->Copy());

    while(fcfs->IsProcessing() || sjf->IsProcessing() || rr->IsProcessing())
    {
        timer->IncreaseTime(1);
    }

    ProcessSchedulerLog* FCFSlog = new ProcessSchedulerLog(queue->Copy());
    ProcessSchedulerLog* SJFlog = new ProcessSchedulerLog(queue->Copy());
    ProcessSchedulerLog* RRlog = new ProcessSchedulerLog(queue->Copy());

    cout << "FCFS " << FCFSlog->ToString() << endl;
    cout << "SJF " << SJFlog->ToString() << endl;
    cout << "RR " << RRlog->ToString() << endl;
}


int main()
{
    vector<Process*> allProcesses = readDataFromFile();

    testFCFS(clone_vector_and_items(allProcesses));
    testSJF(clone_vector_and_items(allProcesses));
    testRR(clone_vector_and_items(allProcesses));
    
    return 0;
}