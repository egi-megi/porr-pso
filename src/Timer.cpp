#include "../include/Timer.h"

#include <sys/time.h>

Timer::Timer()
{
    struct timeval s;
    gettimeofday( &s , nullptr ) ;
    start_time = s.tv_sec + 1e-6 * s.tv_usec ;
}

double Timer::click()
{
    struct timeval s;
    gettimeofday( &s , nullptr );
    return s.tv_sec + 1e-6 * s.tv_usec - start_time;
}