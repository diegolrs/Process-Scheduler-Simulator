#pragma once

class Process
{
    private:
        float enteringTime;
        float returnTime;
        float answerTime;
        float waitTime;

    public:
        Process(float enteringTime=0);

        void InscreaseReturnTime(float v);
        void InscreaseAnswerTime(float v);
        void InscreaseWaitTime(float v);

        // Getters
        float GetEnteringTime() const ;
        float GetReturnTime() const;
        float GetAnswerTime() const;
        float GetWaitTime() const;
};