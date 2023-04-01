#include "TimeStamp_Subject.hpp"

class TimeStamp : public TimeStamp_Subject
{
    public:
        TimeStamp();
        void IncreaseTime(float delta);
        float GetTime();
        float GetMessage() override;
    private:
        float time;
};