#pragma once
/*
#include <SDL.h>

class Clock {
public:
    Clock();

    // Restart the clock and return elapsed time in seconds
    float restart();

private:
    Uint32 m_startTime;
};

*/













#include <SDL.h>

class Clock {
public:
    Clock();

    float restart();

private:
    Uint64 m_startTime;
    double m_frequency;
};



