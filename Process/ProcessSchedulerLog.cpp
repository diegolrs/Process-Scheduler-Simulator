#include "ProcessSchedulerLog.hpp"
#include <iomanip>
#include <algorithm>

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

std::string ProcessSchedulerLog::ToString(int precision, bool useComma)
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(precision) << returnTimeAverage << " ";
    ss << std::fixed << std::setprecision(precision) << answerTimeAverage << " ";
    ss << std::fixed << std::setprecision(precision) << waitTimeAverage;

    std::string _out = ss.str();

    if(useComma)
        std::replace(_out.begin(), _out.end(), '.', ',');

    return _out;
}

void ProcessSchedulerLog::ResetValues()
{
    returnTimeAverage = 0;
    answerTimeAverage = 0;
    waitTimeAverage = 0;
}