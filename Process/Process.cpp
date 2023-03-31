#include "Process.hpp"

Process::Process(float enteringTime)
{
    this->enteringTime = enteringTime;
    this->returnTime = 0;
    this->answerTime = 0;
    this->waitTime = 0;
}

void Process::InscreaseReturnTime(float v) { returnTime += v; }
void Process::InscreaseAnswerTime(float v) { answerTime += v; }
void Process::InscreaseWaitTime(float v)  { waitTime += v; }

// Getters
float Process::GetEnteringTime() const { return enteringTime; }
float Process::GetReturnTime() const { return returnTime; }
float Process::GetAnswerTime() const { return answerTime; }
float Process::GetWaitTime() const { return waitTime; }