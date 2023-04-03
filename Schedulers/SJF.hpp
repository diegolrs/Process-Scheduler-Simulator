#include "../Queue/Queue.hpp"
#include "../Queue/QueueUtils.hpp"
#include "../Process/Process.hpp"
#include "../TimeStamp/TimeStamp.hpp"
#include "../TimeStamp/TimeStamp_Observer.hpp"

// Shortest Job First
class SJF : public TimeStamp_Observer
{
    public:
        SJF(TimeStamp* sender, Queue<Process*>* processQueue);
        void Update(float delta) override;
        bool IsProcessing();
    private:
        Queue<Process*>* allProcessQueue;
        Queue<Process*>* toCreateQueue;
        Queue<Process*>* readyQueue;
        Process* currentProcessing;

        // Send shortest process to head
        void SortReadyQueue();

        void ProcessToCreateQueue(float delta);
        void ProcessCurrentEnabled(float delta);
        void ProcessReadyQueue(float delta);
        void ProcessNext();
        void SetCurrentProcess(Process* p);
};