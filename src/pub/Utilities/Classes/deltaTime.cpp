#include <deltaTime.h>
#include <windows.h>
#include <iostream>

double Time::deltaTime(double timer)
{
    double current_time = timer;
    double MIN_LATENCY = 0.1873f;
    double MAX_LATENCY = 10.999f;
    double TIME_DIVIDER = 6.829f;
    double time_final = (current_time - ((MIN_LATENCY + MAX_LATENCY) / TIME_DIVIDER)) / (TIME_DIVIDER * 2);
    double deltaTime = time_final;

    return deltaTime;
}