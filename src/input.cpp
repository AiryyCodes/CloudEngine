#include "CloudEngine/input.h"
#include <GLFW/glfw3.h>

bool Input::keys[348];
bool Input::keysHeld[348];

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
