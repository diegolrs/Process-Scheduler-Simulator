#include "../Queue/Queue.hpp"
#include "../Process/Process.hpp"

// First-Come, First-Served
class FCFS
{
    public:
        FCFS(Queue<Process*>* processQueue)
        {
            this->toCreateQueue = processQueue;
        }

        void OnTimeStamp(float delta)
        {
            ProcessReadyQueue(delta);
            ProcessWaitingQueue(delta);
        }
    private:
        Queue<Process*>* toCreateQueue;
        Queue<Process*>* readyQueue;
        Process* currentProcessing;

        // TODO: No lugar de delta, por tempo passado atual
        void ProcessToCreateQueue(float delta)
        {
            int length = toCreateQueue->Length();

            for(int i = 0; i < length; i++)
            {
                Process* p = toCreateQueue->Dequeue();

                if(p->GetEnteringTime() >= delta)
                    readyQueue->Enqueue(p);
                else
                    toCreateQueue->Enqueue(p);
            }
        }

        void ProcessReadyQueue(float delta)
        {
            if(currentProcessing == nullptr)
                return;

            currentProcessing->InscreaseInCPUTime(delta);

            if(currentProcessing->IsFinished())
                currentProcessing = readyQueue->Dequeue();
        }

        void ProcessWaitingQueue(float delta)
        {
            int length = readyQueue->Length();

            // iterar fila e aplicar tempo
            for(int i = 0; i < length; i++)
            {
                Process* p = readyQueue->Dequeue();
                p->InscreaseWaitTime(delta);
                readyQueue->Enqueue(p);
            }
        }
};