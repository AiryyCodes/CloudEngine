#include "CloudEngine/core/input.h"

#include <GLFW/glfw3.h>

bool Input::keys[348];
bool Input::keysHeld[348];

float Input::mouseX;
float Input::mouseY;

bool Input::mouseButtons[7];
bool Input::mouseButtonsHeld[7];

void Input::OnKeyHandler(int key, int scancode, int action, int mods)
{
    keys[key] = action == GLFW_PRESS;
    keysHeld[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

bool Input::IsKeyDown(int key)
{
    bool state = keys[key];
    keys[key] = false;
    return state;
}

bool Input::IsKeyHeld(int key)
{
    return keysHeld[key];
}

void Input::OnMousePosHandler(float xPos, float yPos)
{
    mouseX = xPos;
    mouseY = yPos;
}

float Input::GetMouseX()
{
    return mouseX;
}

float Input::GetMouseY()
{
    return mouseY;
}

void Input::OnMouseButtonHandler(int button, int action, int mods)
{
    mouseButtons[button] = action == GLFW_PRESS;
    mouseButtonsHeld[button] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

bool Input::IsMouseDown(int button)
{
    bool state = mouseButtons[button];
    mouseButtons[button] = false;
    return state;
}

bool Input::IsMouseHeld(int button)
{
    return mouseButtonsHeld[button];
}
