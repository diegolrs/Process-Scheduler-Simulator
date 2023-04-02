#include "../Queue/Queue.hpp"
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
};