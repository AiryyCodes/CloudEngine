#pragma once

class Time
{
public:
    static void Update();

    static float GetDelta() { return deltaTime; }

    static void Start();
    static double End();

private:
    static float deltaTime;
};
