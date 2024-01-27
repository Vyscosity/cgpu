/*
// Clock.cpp
#include "Clock.h"

Clock::Clock() : m_startTime(0) {}

float Clock::restart() {
    Uint32 currentTime = SDL_GetTicks();
    float elapsedSeconds = static_cast<float>(currentTime - m_startTime) / 1000.0f;
    m_startTime = currentTime;
    return elapsedSeconds;
}
*/










// Clock.cpp
#include "Clock.h"

Clock::Clock() : m_startTime(0) {
    m_frequency = static_cast<double>(SDL_GetPerformanceFrequency());
}

float Clock::restart() {
    Uint64 currentTime = SDL_GetPerformanceCounter();
    double elapsedSeconds = static_cast<double>(currentTime - m_startTime) / m_frequency;
    m_startTime = currentTime;
    return static_cast<float>(elapsedSeconds);
}