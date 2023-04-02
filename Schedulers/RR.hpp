#include "../Queue/Queue.hpp"
#include "../Process/Process.hpp"
#include "../TimeStamp/TimeStamp.hpp"
#include "../TimeStamp/TimeStamp_Observer.hpp"

//Round Robin
class RR : public TimeStamp_Observer
{
    public:
        RR(TimeStamp* sender, Queue<Process*>* processQueue, float quantum=2);
        void Update(float delta) override;
        bool IsProcessing();
    private:
        Queue<Process*>* allProcessQueue;
        Queue<Process*>* toCreateQueue;
        Queue<Process*>* readyQueue;
        Process* currentProcessing;

        float quantumMax;
        float curQuantum;

        void OnQuantumTick(float quantum);
        void ProcessToCreateQueue(float delta);
        void ProcessCurrentEnabled(float delta);
        void ProcessReadyQueue(float delta);
        void ProcessNext(float quantum);
        void SetCurrentProcess(Process* p);
};