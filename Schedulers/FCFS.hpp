#include "../Queue/Queue.hpp"
#include "../Process/Process.hpp"
#include "../TimeStamp/TimeStamp.hpp"
#include "../TimeStamp/TimeStamp_Observer.hpp"

// First-Come, First-Served
// Return Time: Time to process be completely processed
// Answer Time: Time to process go to CPU for the first time
// Waiting Time: Time that process spent at Ready's Queue
class FCFS : public TimeStamp_Observer
{
    public:
        FCFS(TimeStamp* sender, Queue<Process*>* processQueue);
        void Update(float delta) override;
        bool IsProcessing();
    private:
        Queue<Process*>* allProcessQueue;
        Queue<Process*>* toCreateQueue;
        Queue<Process*>* readyQueue;
        Process* currentProcessing;

        void ProcessToCreateQueue(float delta);
        void ProcessCurrentEnabled(float delta);
        void ProcessReadyQueue(float delta);
        void ProcessNext();
        void SetCurrentProcess(Process* p);
};