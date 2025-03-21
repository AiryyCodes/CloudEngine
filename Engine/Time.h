#pragma once

class Time
{
public:
    static void Update();

    static float GetDelta() { return deltaTime; }
    static float GetFPS() { return 1 / GetDelta(); };

    static void Start();
    static double End();

private:
    static float deltaTime;
};
