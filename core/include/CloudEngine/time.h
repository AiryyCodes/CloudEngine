#pragma once

class Time
{
public:
    inline static float GetDelta() { return delta; }

    static void Update();

private:
    static float delta;
    static float lastFrame;
};
