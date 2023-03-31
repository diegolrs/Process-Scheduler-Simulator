class TimeStamp
{
    public:
        TimeStamp()
        {
            time = 0;
        }   
        
        void IncreaseTime(float delta)
        {
            time += delta;
        }

        float GetTime()
        {
            return time;
        }

    private:
        float time;
};