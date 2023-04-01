#include "FCFS.hpp"

FCFS::FCFS(TimeStamp* sender, Queue<Process*>* processQueue) : TimeStamp_Observer(sender)
{
    this->allProcessQueue = processQueue->Copy();
    this->toCreateQueue = processQueue->Copy();
    this->readyQueue = new Queue<Process*>();

    SetCurrentProcess(nullptr);
    Update(0); // first processment
}

void FCFS::Update(float delta)
{
    ProcessReadyQueue(delta);
    ProcessToCreateQueue(delta);
    ProcessCurrentEnabled(delta);
    ProcessNext();
}

bool FCFS::IsProcessing()
{
    for(int i = 0; i < allProcessQueue->Length(); i++)
    {
        Process* p = allProcessQueue->Dequeue();
        allProcessQueue->Enqueue(p);

        if(!p->IsFinished())
            return true;
    }

    return false;
}

void FCFS::ProcessToCreateQueue(float delta)
{
    int length = toCreateQueue->Length();

    for(int i = 0; i < length; i++)
    {
        Process* p = toCreateQueue->Dequeue();

        if(sender->GetTotalTime() >= p->GetEnteringTime())
            readyQueue->Enqueue(p);
        else
            toCreateQueue->Enqueue(p);
    }
}

void FCFS::ProcessCurrentEnabled(float delta)
{
    if(currentProcessing == nullptr)
        SetCurrentProcess(readyQueue->Dequeue());

    if(currentProcessing != nullptr && !currentProcessing->IsFinished()) 
        currentProcessing->InscreaseInCPUTime(delta);
}

void FCFS::ProcessReadyQueue(float delta)
{
    for(int i = 0; i < readyQueue->Length(); i++)
    {
        Process* p = readyQueue->Dequeue();
        p->InscreaseWaitTime(delta);
        readyQueue->Enqueue(p);
    }
}

void FCFS::ProcessNext()
{
    bool shouldSwitchCurrentProcess = currentProcessing && currentProcessing->IsFinished();
  
    if(shouldSwitchCurrentProcess)
    {
        float returnTime = sender->GetTotalTime() - currentProcessing->GetEnteringTime();
        currentProcessing->SetReturnTime(returnTime);
        SetCurrentProcess(readyQueue->IsEmpty() ? nullptr : readyQueue->Dequeue());    
    }
}

void FCFS::SetCurrentProcess(Process* p)
{
    currentProcessing = p;

    if(p == nullptr)
        return;

    float curTime = sender->GetTotalTime();
    float init = p->GetEnteringTime();
    float answerTime = curTime - init;
    currentProcessing->SetAnswerTime(answerTime);
}