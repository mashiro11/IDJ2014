#ifndef TIMER_H
#define TIMER_H


class Timer
{
    public:
        Timer();
        //~Timer();
        void Update (float dt);
        void Restart ();
        float Get();
        void Set(float value);
    protected:
        /* vazio */
    private:
        float time;
};
#endif // TIMER_H
