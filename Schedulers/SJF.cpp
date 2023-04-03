#include "SJF.hpp"

SJF::SJF(TimeStamp* sender, Queue<Process*>* processQueue) : TimeStamp_Observer(sender)
{
    this->allProcessQueue = processQueue->Copy();
    this->toCreateQueue = processQueue->Copy();
    this->readyQueue = new Queue<Process*>();

    // first processment
    SetCurrentProcess(nullptr);
    ProcessToCreateQueue(0);
    ProcessNext();
}

void SJF::Update(float delta)
{
    ProcessReadyQueue(delta);
    ProcessCurrentEnabled(delta);
    ProcessToCreateQueue(delta);
    ProcessNext();
}

// TODO: Move to be inside class
bool SJF_SortingFunction(Process* p1, Process* p2) 
{
    return (p1->GetDurationLeft() <= p2->GetDurationLeft()); 
}

void SJF::SortReadyQueue()
{
    if(readyQueue->Length() > 0)
        readyQueue = QueueUtils::sort_queue(readyQueue, SJF_SortingFunction);
}

bool SJF::IsProcessing()
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

void SJF::ProcessToCreateQueue(float delta)
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

void SJF::ProcessCurrentEnabled(float delta)
{
    if(currentProcessing != nullptr)
    {
        currentProcessing->InscreaseInCPUTime(delta);

        if(currentProcessing->IsFinished())
            currentProcessing->SetReturnTime(sender->GetTotalTime() - currentProcessing->GetEnteringTime());;
    }
}

void SJF::ProcessReadyQueue(float delta)
{
    for(int i = 0; i < readyQueue->Length(); i++)
    {
        Process* p = readyQueue->Dequeue();
        p->InscreaseWaitTime(delta);
        readyQueue->Enqueue(p);
    }
}

void SJF::ProcessNext()
{
    // Returns process enabled to Ready Queue
    if(currentProcessing != nullptr && !currentProcessing->IsFinished())
        readyQueue->Enqueue(currentProcessing);

    SortReadyQueue(); // send shortest to head
    SetCurrentProcess(readyQueue->IsEmpty() ? nullptr : readyQueue->Dequeue()); 
}

void SJF::SetCurrentProcess(Process* p)
{
    currentProcessing = p;

    if(currentProcessing && !currentProcessing->HasBeenOnCPU())
    {
        currentProcessing->TriggerHasBeenOnCPU();

        float curTime = sender->GetTotalTime();
        float init = currentProcessing->GetEnteringTime();
        float answerTime = curTime - init;
        currentProcessing->SetAnswerTime(answerTime);
    }
}
