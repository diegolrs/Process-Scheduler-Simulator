#pragma once
#include <string>
#include <sstream>
#include "../Queue/Queue.hpp"
#include "../Process/Process.hpp"

struct ProcessSchedulerLog
{
    public:
        ProcessSchedulerLog(Queue<Process*>* processQueue);
        void CalculateLog(Queue<Process*>* processQueue);
        std::string ToString();

    private:
        float returnTimeAverage;
        float answerTimeAverage;
        float waitTimeAverage;
        void ResetValues();
};