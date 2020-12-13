#ifndef ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_TIMER_H
#define ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_TIMER_H

class Timer
{
public:
    Timer();
    virtual ~Timer() = default;

    double click();

private:
    double start_time;
};

#endif // ROJCZASTEK_SZCZEPANSKI_JURKIEWICZ_PIKULINSKI_TIMER_H