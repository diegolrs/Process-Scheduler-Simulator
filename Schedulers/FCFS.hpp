#include "../Queue/Queue.hpp"
#include "../Process/Process.hpp"
#include "../TimeStamp/TimeStamp.hpp"
#include "../TimeStamp/TimeStamp_Observer.hpp"

// First-Come, First-Served
class FCFS : public TimeStamp_Observer
{
    public:
        FCFS(TimeStamp* sender, Queue<Process*>* processQueue);
        void Update(float delta) override;
    private:
        Queue<Process*>* allProcessQueue;
        Queue<Process*>* toCreateQueue;
        Queue<Process*>* readyQueue;
        Process* currentProcessing;

        void ProcessToCreateQueue(float delta);
        void ProcessCurrentEnabled(float delta);
        void ProcessReadyQueue(float delta);
        Process* GetNextToBeProcessed();
};