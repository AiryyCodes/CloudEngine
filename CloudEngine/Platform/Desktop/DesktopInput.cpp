#include "CloudEngine/Application.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Input.h"
#include "CloudEngine/Window/Window.h"

#include <GLFW/glfw3.h>
#include <cstdio>

static bool keysDown[512];
static bool keysHeld[512];

static double mouseX;
static double mouseY;
static double lastMouseX;
static double lastMouseY;
static bool firstMouse = true;

void Input::Update()
{
    if (GetCursorMode() == CursorMode::Unlocked)
    {
        firstMouse = true;
    }
    // lastMouseX = 0.0f;
    // lastMouseY = 0.0f;
}

void Input::UpdateEnd()
{
    // lastMouseX = 0.0f;
    // lastMouseY = 0.0f;
}

bool Input::IsKeyDown(Key key)
{
    return keysHeld[ConvertKey(key)];
}

bool Input::IsKeyJustDown(Key key)
{
    bool state = keysDown[ConvertKey(key)];
    keysDown[ConvertKey(key)] = false;
    return state;
}

void Input::KeyCallback(Key key, int scancode, int action, int mods)
{
    keysDown[ConvertKey(key)] = action == GLFW_PRESS;
    keysHeld[ConvertKey(key)] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

float Input::GetMouseX()
{
    return mouseX;
}

float Input::GetMouseY()
{
    return mouseY;
}

glm::vec2 Input::GetMouseDelta()
{
    if (firstMouse)
    {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        firstMouse = false;
    }

    float deltaX = mouseX - lastMouseX;
    float deltaY = lastMouseY - mouseY;

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    return {deltaX, deltaY};
}

CursorMode Input::GetCursorMode()
{
    return Application::Get().GetMainWindow()->GetCursorMode();
}

void Input::SetCursorMode(CursorMode mode)
{
    Application::Get().GetMainWindow()->SetCursorMode(mode);
}

void Input::ToggleCursor()
{
    Ref<Window> window = Application::Get().GetMainWindow();
    CursorMode mode = window->GetCursorMode();
    window->SetCursorMode(mode == CursorMode::Locked ? CursorMode::Unlocked : CursorMode::Locked);
}

void Input::MousePosCallback(double x, double y)
{
    mouseX = x;
    mouseY = y;
}

bool Input::IsTouching(int numFingers)
{
    return false;
}

bool Input::IsJustTouching(int numFingers)
{
    return false;
}

bool Input::IsTouchingEnd(int numFingers)
{
    return false;
}

glm::vec2 Input::GetSwipe()
{
    return {0.0f, 0.0f};
}

float Input::GetPinch()
{
    return 0.0;
}

void Input::TouchCallback(int touches, TouchPhase phase, double x, double y)
{
}

int Input::ConvertKey(Key key)
{
    switch (key)
    {
    case Key::A:
        return GLFW_KEY_A;
    case Key::B:
        return GLFW_KEY_B;
    case Key::C:
        return GLFW_KEY_C;
    case Key::D:
        return GLFW_KEY_D;
    case Key::E:
        return GLFW_KEY_E;
    case Key::F:
        return GLFW_KEY_F;
    case Key::G:
        return GLFW_KEY_G;
    case Key::H:
        return GLFW_KEY_H;
    case Key::I:
        return GLFW_KEY_I;
    case Key::J:
        return GLFW_KEY_J;
    case Key::K:
        return GLFW_KEY_K;
    case Key::L:
        return GLFW_KEY_L;
    case Key::M:
        return GLFW_KEY_M;
    case Key::N:
        return GLFW_KEY_N;
    case Key::O:
        return GLFW_KEY_O;
    case Key::P:
        return GLFW_KEY_P;
    case Key::Q:
        return GLFW_KEY_Q;
    case Key::R:
        return GLFW_KEY_R;
    case Key::S:
        return GLFW_KEY_S;
    case Key::T:
        return GLFW_KEY_T;
    case Key::U:
        return GLFW_KEY_U;
    case Key::V:
        return GLFW_KEY_V;
    case Key::W:
        return GLFW_KEY_W;
    case Key::X:
        return GLFW_KEY_X;
    case Key::Y:
        return GLFW_KEY_Y;
    case Key::Z:
        return GLFW_KEY_Z;
    case Key::Zero:
        return GLFW_KEY_0;
    case Key::One:
        return GLFW_KEY_1;
    case Key::Two:
        return GLFW_KEY_2;
    case Key::Three:
        return GLFW_KEY_3;
    case Key::Four:
        return GLFW_KEY_4;
    case Key::Five:
        return GLFW_KEY_5;
    case Key::Six:
        return GLFW_KEY_6;
    case Key::Seven:
        return GLFW_KEY_7;
    case Key::Eight:
        return GLFW_KEY_8;
    case Key::Nine:
        return GLFW_KEY_9;
    case Key::Space:
        return GLFW_KEY_SPACE;
    case Key::Apostrophe:
        return GLFW_KEY_APOSTROPHE; // TODO: Find the right enum value in glfm
    case Key::Comma:
        return GLFW_KEY_COMMA;
    case Key::Minus:
        return GLFW_KEY_MINUS;
    case Key::Period:
        return GLFW_KEY_PERIOD;
    case Key::Slash:
        return GLFW_KEY_SLASH;
    case Key::Semicolon:
        return GLFW_KEY_SEMICOLON;
    case Key::Equal:
        return GLFW_KEY_EQUAL;
    case Key::LeftBracket:
        return GLFW_KEY_LEFT_BRACKET;
    case Key::RightBracket:
        return GLFW_KEY_RIGHT_BRACKET;
    case Key::Grave:
        return GLFW_KEY_GRAVE_ACCENT;
    case Key::Escape:
        return GLFW_KEY_ESCAPE;
    case Key::Enter:
        return GLFW_KEY_ENTER;
    case Key::Tab:
        return GLFW_KEY_TAB;
    case Key::Backspace:
        return GLFW_KEY_BACKSPACE;
    case Key::Insert:
        return GLFW_KEY_INSERT;
    case Key::Delete:
        return GLFW_KEY_DELETE;
    case Key::Left:
        return GLFW_KEY_LEFT;
    case Key::Right:
        return GLFW_KEY_RIGHT;
    case Key::Up:
        return GLFW_KEY_UP;
    case Key::Down:
        return GLFW_KEY_DOWN;
    case Key::PageUp:
        return GLFW_KEY_PAGE_UP;
    case Key::PageDown:
        return GLFW_KEY_PAGE_DOWN;
    case Key::Home:
        return GLFW_KEY_HOME;
    case Key::End:
        return GLFW_KEY_END;
    case Key::CapsLock:
        return GLFW_KEY_CAPS_LOCK;
    case Key::ScrollLock:
        return GLFW_KEY_SCROLL_LOCK;
    case Key::NumLock:
        return GLFW_KEY_NUM_LOCK;
    case Key::PrintScreen:
        return GLFW_KEY_PRINT_SCREEN;
    case Key::Pause:
        return GLFW_KEY_PAUSE;
    case Key::F1:
        return GLFW_KEY_F1;
    case Key::F2:
        return GLFW_KEY_F2;
    case Key::F3:
        return GLFW_KEY_F3;
    case Key::F4:
        return GLFW_KEY_F4;
    case Key::F5:
        return GLFW_KEY_F5;
    case Key::F6:
        return GLFW_KEY_F6;
    case Key::F7:
        return GLFW_KEY_F7;
    case Key::F8:
        return GLFW_KEY_F8;
    case Key::F9:
        return GLFW_KEY_F9;
    case Key::F10:
        return GLFW_KEY_F10;
    case Key::F11:
        return GLFW_KEY_F11;
    case Key::F12:
        return GLFW_KEY_F12;
    case Key::F13:
        return GLFW_KEY_F13;
    case Key::F14:
        return GLFW_KEY_F14;
    case Key::F15:
        return GLFW_KEY_F15;
    case Key::F16:
        return GLFW_KEY_F16;
    case Key::F17:
        return GLFW_KEY_F17;
    case Key::F18:
        return GLFW_KEY_F18;
    case Key::F19:
        return GLFW_KEY_F19;
    case Key::F20:
        return GLFW_KEY_F20;
    case Key::F21:
        return GLFW_KEY_F21;
    case Key::F22:
        return GLFW_KEY_F22;
    case Key::F23:
        return GLFW_KEY_F23;
    case Key::F24:
        return GLFW_KEY_F24;
    case Key::F25:
        return GLFW_KEY_F25;
    case Key::Numpad0:
        return GLFW_KEY_KP_0;
    case Key::Numpad1:
        return GLFW_KEY_KP_1;
    case Key::Numpad2:
        return GLFW_KEY_KP_2;
    case Key::Numpad3:
        return GLFW_KEY_KP_3;
    case Key::Numpad4:
        return GLFW_KEY_KP_4;
    case Key::Numpad5:
        return GLFW_KEY_KP_5;
    case Key::Numpad6:
        return GLFW_KEY_KP_6;
    case Key::Numpad7:
        return GLFW_KEY_KP_7;
    case Key::Numpad8:
        return GLFW_KEY_KP_8;
    case Key::Numpad9:
        return GLFW_KEY_KP_9;
    case Key::NumpadDecimal:
        return GLFW_KEY_KP_DECIMAL;
    case Key::NumpadDivide:
        return GLFW_KEY_KP_DIVIDE;
    case Key::NumpadMultiply:
        return GLFW_KEY_KP_MULTIPLY;
    case Key::NumpadSubtract:
        return GLFW_KEY_KP_SUBTRACT;
    case Key::NumpadAdd:
        return GLFW_KEY_KP_ADD;
    case Key::NumpadEnter:
        return GLFW_KEY_KP_ENTER;
    case Key::NumpadEqual:
        return GLFW_KEY_KP_EQUAL;
    case Key::LeftShift:
        return GLFW_KEY_LEFT_SHIFT;
    case Key::LeftControl:
        return GLFW_KEY_LEFT_CONTROL;
    case Key::LeftAlt:
        return GLFW_KEY_LEFT_ALT;
    case Key::LeftSuper:
        return GLFW_KEY_LEFT_SUPER;
    case Key::RightShift:
        return GLFW_KEY_RIGHT_SHIFT;
    case Key::RightControl:
        return GLFW_KEY_RIGHT_CONTROL;
    case Key::RightAlt:
        return GLFW_KEY_RIGHT_ALT;
    case Key::RightSuper:
        return GLFW_KEY_RIGHT_SUPER;
    case Key::Menu:
        return GLFW_KEY_MENU;
    default:
        return -1;
    }
}