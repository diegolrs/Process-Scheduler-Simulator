#pragma once
#include <string>

class Process
{
    private:
        float enteringTime;
        float durationTime;
        float inCPUTime;

        float returnTime;
        float answerTime;
        float waitTime;

        bool alreadyHasBeenOnCPU;
    public:
        Process(float enteringTime=0, float durationTime=0);

        bool IsFinished() const;
        std::string ToString();

        void InscreaseReturnTime(float v);
        void InscreaseAnswerTime(float v);
        void InscreaseWaitTime(float v);
        void InscreaseInCPUTime(float v);

        bool HasBeenOnCPU();
        void TriggerHasBeenOnCPU(); // set as true

        // Getters
        float GetEnteringTime() const;
        float GetDurationTime() const;
        float GetDurationLeft() const;
        float GetInCPUTime() const;
        float GetReturnTime() const;
        float GetAnswerTime() const;
        float GetWaitTime() const; 

        // Setters
        void SetEnteringTime(float enteringTime);
        void SetDurationTime(float durationTime);
        void SetInCPUTime(float inCPUTime);
        void SetReturnTime(float returnTime);
        void SetAnswerTime(float answerTime);
        void SetWaitTime(float waitTime);
};