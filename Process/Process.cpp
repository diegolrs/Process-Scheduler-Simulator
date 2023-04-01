#include "Process.hpp"

Process::Process(float enteringTime, float durationTime)
{
    this->enteringTime = enteringTime;
    this->durationTime = durationTime;
    
    this->inCPUTime = 0;
    this->returnTime = 0;
    this->answerTime = 0;
    this->waitTime = 0;
}

bool Process::IsFinished() const { return inCPUTime >= durationTime; }

std::string Process::ToString()
{
    std::string msg = "";

    msg += "[ReturnTime]: " + std::to_string(returnTime) + "\n";
    msg += "[AnswerTim]: " + std::to_string(answerTime) + "\n";
    msg += "[WaitTime]: " + std::to_string(waitTime) + "\n";
    msg += "[InCPUTime]: " + std::to_string(inCPUTime) + "\n";

    return msg;
}

void Process::InscreaseReturnTime(float v) { returnTime += v; }
void Process::InscreaseAnswerTime(float v) { answerTime += v; }
void Process::InscreaseWaitTime(float v)  { waitTime += v; }
void Process::InscreaseInCPUTime(float v)  {inCPUTime += v; }

// Getters
float Process::GetEnteringTime() const { return enteringTime; }
float Process::GetDurationTime() const { return durationTime; }
float Process::GetInCPUTime() const { return inCPUTime; }
float Process::GetReturnTime() const { return returnTime; }
float Process::GetAnswerTime() const { return answerTime; }
float Process::GetWaitTime() const { return waitTime; }