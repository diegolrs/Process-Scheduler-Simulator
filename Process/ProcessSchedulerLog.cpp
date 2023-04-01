#include "ProcessSchedulerLog.hpp"

ProcessSchedulerLog::ProcessSchedulerLog(Queue<Process*>* processQueue)
{
    ResetValues();
    CalculateLog(processQueue);
}

void ProcessSchedulerLog::CalculateLog(Queue<Process*>* processQueue)
{
    int size = processQueue->Length();

    if(size <= 0)
        return;

    for(int i = 0; i < size; i++)
    {
        Process* p = processQueue->Dequeue();
        returnTimeAverage += p->GetReturnTime();
        answerTimeAverage += p->GetAnswerTime();
        waitTimeAverage += p->GetWaitTime();
    }

    float averageMultiplier = 1.0f/size;
    returnTimeAverage *= averageMultiplier;
    answerTimeAverage *= averageMultiplier;
    waitTimeAverage *= averageMultiplier;
}

std::string ProcessSchedulerLog::ToString()
{
    std::ostringstream ss;
    ss << returnTimeAverage << " ";
    ss << answerTimeAverage << " ";
    ss << waitTimeAverage;
    return ss.str();
}

void ProcessSchedulerLog::ResetValues()
{
    returnTimeAverage = 0;
    answerTimeAverage = 0;
    waitTimeAverage = 0;
}