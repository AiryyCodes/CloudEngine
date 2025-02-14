#include "Time.h"
#include <chrono>

float Time::deltaTime = 0.0f;
std::chrono::steady_clock::time_point lastUpdate;

void Time::Update()
{
    auto now = std::chrono::steady_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
    lastUpdate = now;
}