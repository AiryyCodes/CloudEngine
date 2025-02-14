#include "Time.h"

#include <chrono>

float Time::deltaTime = 0.0f;
std::chrono::steady_clock::time_point lastUpdate;

std::chrono::time_point start = std::chrono::high_resolution_clock::time_point::min();

void Time::Update()
{
    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
    lastUpdate = now;
}

void Time::Start()
{
    start = std::chrono::high_resolution_clock::now();
}

double Time::End()
{
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}
