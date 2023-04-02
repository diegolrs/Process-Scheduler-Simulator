#include "RR.hpp"
#include <iostream>

RR::RR(TimeStamp* sender, Queue<Process*>* processQueue, float quantum) : TimeStamp_Observer(sender)
{
    this->curQuantum = 0;
    this->quantumMax = quantum;

    this->allProcessQueue = processQueue->Copy();
    this->toCreateQueue = processQueue->Copy();
    this->readyQueue = new Queue<Process*>();

    // first processment
    SetCurrentProcess(nullptr);
    Update(0);
    ProcessNext(0);
}

void RR::Update(float delta)
{
    curQuantum += delta;

    bool quantumFinished = curQuantum >= quantumMax;
    bool processFinished = currentProcessing && currentProcessing->IsFinished();

    ProcessReadyQueue(delta); // increase na fila de espera
    ProcessToCreateQueue(delta); // coloquei na fila de prontos
    ProcessCurrentEnabled(delta); // adicionei tempo na cpu

    if(quantumFinished || processFinished)
    {
        ProcessNext(curQuantum);
        curQuantum = 0; //-= quantumMax;
    }
}

bool RR::IsProcessing()
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

void RR::ProcessToCreateQueue(float delta)
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

void RR::ProcessCurrentEnabled(float delta)
{
    // if(currentProcessing == nullptr)
    //     SetCurrentProcess(readyQueue->Dequeue());

    if(currentProcessing != nullptr && !currentProcessing->IsFinished()) 
    {
        //currentProcessing->InscreaseReturnTime(delta);
        currentProcessing->InscreaseInCPUTime(delta);
    }
}

void RR::ProcessReadyQueue(float delta)
{
    for(int i = 0; i < readyQueue->Length(); i++)
    {
        Process* p = readyQueue->Dequeue();
        p->InscreaseWaitTime(delta);
        readyQueue->Enqueue(p);
    }
}

void RR::ProcessNext(float quantum)
{
    // Returns unfinished process to Ready Queue
    if(currentProcessing)
    {
        if(!currentProcessing->IsFinished())
            readyQueue->Enqueue(currentProcessing);
        else
            currentProcessing->SetReturnTime(sender->GetTotalTime() - currentProcessing->GetEnteringTime());
    }

    SetCurrentProcess(readyQueue->IsEmpty() ? nullptr : readyQueue->Dequeue()); 
}

void RR::SetCurrentProcess(Process* p)
{
    currentProcessing = p;

    if(p == nullptr)
        return;

    if(!currentProcessing->HasBeenOnCPU())
    {
        currentProcessing->TriggerHasBeenOnCPU();
        float curTime = sender->GetTotalTime();
        float init = p->GetEnteringTime();
        float answerTime = curTime - init;
        currentProcessing->SetAnswerTime(answerTime);
    }
}