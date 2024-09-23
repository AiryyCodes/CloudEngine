#pragma once

class Input
{
public:
    static void OnKeyHandler(int key, int scancode, int action, int mods);

    static bool IsKeyDown(int key);
    static bool IsKeyHeld(int key);

    static void OnMousePosHandler(float xPos, float yPos);

    static float GetMouseX();
    static float GetMouseY();

    static void SetCursorMode(int mode);
    static void ToggleCursor();
    static bool IsCursorLocked();

private:
    static bool keys[348];
    static bool keysHeld[348];

    static float mouseX;
    static float mouseY;
};
