#pragma once

#include <glm/glm.hpp>

enum class Key
{
    None,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Zero,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Space,
    Apostrophe,
    Comma,
    Minus,
    Period,
    Slash,
    Semicolon,
    Equal,
    LeftBracket,
    RightBracket,
    Grave,
    Escape,
    Enter,
    Tab,
    Backspace,
    Insert,
    Delete,
    Left,
    Right,
    Up,
    Down,
    PageUp,
    PageDown,
    Home,
    End,
    CapsLock,
    ScrollLock,
    NumLock,
    PrintScreen,
    Pause,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    NumpadDecimal,
    NumpadDivide,
    NumpadMultiply,
    NumpadSubtract,
    NumpadAdd,
    NumpadEnter,
    NumpadEqual,
    LeftShift,
    LeftControl,
    LeftAlt,
    LeftSuper,
    RightShift,
    RightControl,
    RightAlt,
    RightSuper,
    Menu,
};

enum class TouchPhase
{
    Hover,
    Begin,
    Move,
    End,
    Cancel
};

enum class CursorMode
{
    Locked,
    Unlocked,
};

class Input
{
public:
    static void Update();
    static void UpdateEnd();

    static bool IsKeyDown(Key key);
    static bool IsKeyJustDown(Key key);

    static void KeyCallback(Key key, int scancode, int action, int mods);
    static int ConvertKey(Key key);

    static float GetMouseX();
    static float GetMouseY();
    static glm::vec2 GetMouseDelta();

    static CursorMode GetCursorMode();
    static void SetCursorMode(CursorMode mode);
    static void ToggleCursor();

    static void MousePosCallback(double x, double y);

    static bool IsTouching(int numFingers);
    static bool IsJustTouching(int numFingers);
    static bool IsTouchingEnd(int numFingers);

    static glm::vec2 GetSwipe();
    static float GetPinch();

    static void TouchCallback(int touches, TouchPhase phase, double x, double y);
};
