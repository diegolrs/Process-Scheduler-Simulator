#include "FCFS.hpp"
#include <iostream>

FCFS::FCFS(TimeStamp* sender, Queue<Process*>* processQueue) : TimeStamp_Observer(sender)
{
    this->allProcessQueue = processQueue;
    this->toCreateQueue = processQueue;
    this->readyQueue = new Queue<Process*>();
    this->currentProcessing = nullptr;
}

void FCFS::Update(float delta)
{
    ProcessToCreateQueue(delta);
    ProcessCurrentEnabled(delta);
    ProcessReadyQueue(delta);

    currentProcessing = GetNextToBeProcessed();
}

void FCFS::ProcessToCreateQueue(float delta)
{
    int length = toCreateQueue->Length();

    for(int i = 0; i < length; i++)
    {
        Process* p = toCreateQueue->Dequeue();

        if(p->GetEnteringTime() < sender->GetTotalTime())
            readyQueue->Enqueue(p);
        else
            toCreateQueue->Enqueue(p);
    }
}

void FCFS::ProcessCurrentEnabled(float delta)
{
    if(currentProcessing == nullptr)
        currentProcessing = readyQueue->Dequeue();

    if(currentProcessing != nullptr)
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

Process* FCFS::GetNextToBeProcessed()
{
    // if should switch current process   
    if(currentProcessing && currentProcessing->IsFinished())
    {
        return readyQueue->IsEmpty() ? nullptr : readyQueue->Dequeue();
    }
        
    return currentProcessing;
}