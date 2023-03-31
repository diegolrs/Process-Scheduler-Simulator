#pragma once

class Process
{
    private:
        float enteringTime;
        float durationTime;
        float inCPUTime;

        float returnTime;
        float answerTime;
        float waitTime;

    public:
        Process(float enteringTime=0, float durationTime=0);

        bool IsFinished() const;

        void InscreaseReturnTime(float v);
        void InscreaseAnswerTime(float v);
        void InscreaseWaitTime(float v);
        void InscreaseInCPUTime(float v);

        // Getters
        float GetEnteringTime() const;
        float GetDurationTime() const;
        float GetInCPUTime() const;
        float GetReturnTime() const;
        float GetAnswerTime() const;
        float GetWaitTime() const; 
};