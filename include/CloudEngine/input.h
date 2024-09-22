#pragma once

class Input
{
public:
    static void OnKeyHandler(int key, int scancode, int action, int mods);

    static bool IsKeyDown(int key);
    static bool IsKeyHeld(int key);

private:
    static bool keys[348];
    static bool keysHeld[348];
};
