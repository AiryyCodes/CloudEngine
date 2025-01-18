#pragma once

class Time
{
public:
    static void Update();

    static float GetDelta() { return deltaTime; }

private:
    static float deltaTime;
};