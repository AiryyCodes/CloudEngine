#include "CloudEngine/Input.h"

#include <GLFW/glfw3.h>

static bool keysDown[GLFW_KEY_LAST];
static bool keysHeld[GLFW_KEY_LAST];

bool Input::IsKeyDown(int key)
{
    return keysHeld[key];
}

bool Input::IsKeyJustDown(int key)
{
    bool state = keysDown[key];
    keysDown[key] = false;
    return state;
}

void Input::KeyCallback(int key, int scancode, int action, int mods)
{
    keysDown[key] = action == GLFW_PRESS;
    keysHeld[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}