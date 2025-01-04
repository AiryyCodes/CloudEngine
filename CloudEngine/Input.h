#pragma once

class Input
{
public:
    static bool IsKeyDown(int key);
    static bool IsKeyJustDown(int key);

    static void KeyCallback(int key, int scancode, int action, int mods);
};