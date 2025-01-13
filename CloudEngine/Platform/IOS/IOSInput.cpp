#include "CloudEngine/Input.h"
#include "CloudEngine/Application.h"

#include <glfm.h>
#include <glm/glm.hpp>

static bool keysDown[512];
static bool keysHeld[512];

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
    keysDown[ConvertKey(key)] = action == GLFMKeyActionPressed;
    keysHeld[ConvertKey(key)] = action == GLFMKeyActionPressed || action == GLFMKeyActionRepeated;
}

struct TouchState
{
    glm::vec2 lastPosition;
    glm::vec2 startPosition;
    glm::vec2 delta;
    bool isTouching;
};

static TouchState firstTouchState;
static TouchState secondTouchState;
static bool isSwiping = false;
static float pinchDelta = 0.0f;   // Stores the pinch delta
static float currentDistance = 0.0f; // Current distance between two touches
static float previousDistance = 0.0f; // Previous distance between two touches

static bool touchBegin[128];
static bool touchJustBegin[128];
static bool touchEnd[128];

bool Input::IsTouching(int numFingers)
{
    return touchBegin[numFingers - 1];
}

bool Input::IsJustTouching(int numFingers)
{
    bool state = touchJustBegin[numFingers - 1];
    touchJustBegin[numFingers - 1] = false; // Reset state after return
    return state;
}

bool Input::IsTouchingEnd(int numFingers)
{
    bool state = touchEnd[numFingers - 1];
    touchEnd[numFingers - 1] = false; // Reset state after return
    return state;
}

glm::vec2 Input::GetSwipe()
{
    glm::vec2 newDelta = {-firstTouchState.delta.x, firstTouchState.delta.y};
    
    firstTouchState.delta.x = 0.0f;
    firstTouchState.delta.y = 0.0f;
    
    return newDelta;
}

float Input::GetPinch()
{
    float newDelta = pinchDelta;
    
    return newDelta;
}

void Input::TouchCallback(int touches, TouchPhase phase, double x, double y)
{
    glm::vec2 currentTouchPosition(x, y);
    
    switch (phase)
    {
        case TouchPhase::Begin:
            if (touches == 0)
            {
                firstTouchState.startPosition = currentTouchPosition;
                firstTouchState.lastPosition = currentTouchPosition;
                firstTouchState.isTouching = true;
            }
            else if (touches == 1)
            {
                secondTouchState.startPosition = currentTouchPosition;
                secondTouchState.lastPosition = currentTouchPosition;
                secondTouchState.isTouching = true;
                // Initialize distances when the second touch begins
                previousDistance = glm::distance(firstTouchState.lastPosition, secondTouchState.lastPosition);
                currentDistance = previousDistance;
                pinchDelta = 0.0f; // Reset pinch delta
            }
            touchBegin[touches] = true;
            touchJustBegin[touches] = true;
            break;
            
        case TouchPhase::Move:
            if (firstTouchState.isTouching && touches == 0)
            {
                firstTouchState.delta = currentTouchPosition - firstTouchState.lastPosition;
                firstTouchState.lastPosition = currentTouchPosition;
            }
            else if (secondTouchState.isTouching && touches == 1)
            {
                secondTouchState.delta = currentTouchPosition - secondTouchState.lastPosition;
                secondTouchState.lastPosition = currentTouchPosition;
                
                // Calculate the current distance and pinch delta
                currentDistance = glm::distance(firstTouchState.lastPosition, secondTouchState.lastPosition);
                static const float smoothingFactor = 0.1f; // Adjust this value for smoother results
                pinchDelta = smoothingFactor * (currentDistance - previousDistance) + (1.0f - smoothingFactor) * pinchDelta;
                previousDistance = currentDistance; // Update previous distance
            }
            break;
            
        case TouchPhase::End:
        case TouchPhase::Cancel:
            if (touches == 0)
            {
                firstTouchState.isTouching = false;
                firstTouchState.delta = glm::vec2(0.0f, 0.0f);
                previousDistance = 0.0f;
                pinchDelta = 0.0f; // Reset pinch delta
            }
            else if (touches == 1)
            {
                secondTouchState.isTouching = false;
                secondTouchState.delta = glm::vec2(0.0f, 0.0f);
                previousDistance = 0.0f;
                pinchDelta = 0.0f; // Reset pinch delta
            }
            touchBegin[touches] = false;
            touchJustBegin[touches] = false;
            touchEnd[touches] = true;
            break;
            
        default:
            break;
    }
}

void Input::Update()
{
    pinchDelta = 0.0f;
    firstTouchState.delta = glm::vec2(0.0f, 0.0f);
    secondTouchState.delta = glm::vec2(0.0f, 0.0f);
}

int Input::ConvertKey(Key key)
{
    switch (key)
    {
        case Key::A:
            return GLFMKeyCodeA;
        case Key::B:
            return GLFMKeyCodeB;
        case Key::C:
            return GLFMKeyCodeC;
        case Key::D:
            return GLFMKeyCodeD;
        case Key::E:
            return GLFMKeyCodeE;
        case Key::F:
            return GLFMKeyCodeF;
        case Key::G:
            return GLFMKeyCodeG;
        case Key::H:
            return GLFMKeyCodeH;
        case Key::I:
            return GLFMKeyCodeI;
        case Key::J:
            return GLFMKeyCodeJ;
        case Key::K:
            return GLFMKeyCodeK;
        case Key::L:
            return GLFMKeyCodeL;
        case Key::M:
            return GLFMKeyCodeM;
        case Key::N:
            return GLFMKeyCodeN;
        case Key::O:
            return GLFMKeyCodeO;
        case Key::P:
            return GLFMKeyCodeP;
        case Key::Q:
            return GLFMKeyCodeQ;
        case Key::R:
            return GLFMKeyCodeR;
        case Key::S:
            return GLFMKeyCodeS;
        case Key::T:
            return GLFMKeyCodeT;
        case Key::U:
            return GLFMKeyCodeU;
        case Key::V:
            return GLFMKeyCodeV;
        case Key::W:
            return GLFMKeyCodeW;
        case Key::X:
            return GLFMKeyCodeX;
        case Key::Y:
            return GLFMKeyCodeY;
        case Key::Z:
            return GLFMKeyCodeZ;
        case Key::Zero:
            return GLFMKeyCode0;
        case Key::One:
            return GLFMKeyCode1;
        case Key::Two:
            return GLFMKeyCode2;
        case Key::Three:
            return GLFMKeyCode3;
        case Key::Four:
            return GLFMKeyCode4;
        case Key::Five:
            return GLFMKeyCode5;
        case Key::Six:
            return GLFMKeyCode6;
        case Key::Seven:
            return GLFMKeyCode7;
        case Key::Eight:
            return GLFMKeyCode8;
        case Key::Nine:
            return GLFMKeyCode9;
        case Key::Space:
            return GLFMKeyCodeSpace;
        case Key::Apostrophe:
            return GLFMKeyCodeUnknown; // TODO: Find the right enum value in glfm
        case Key::Comma:
            return GLFMKeyCodeComma;
        case Key::Minus:
            return GLFMKeyCodeMinus;
        case Key::Period:
            return GLFMKeyCodePeriod;
        case Key::Slash:
            return GLFMKeyCodeSlash;
        case Key::Semicolon:
            return GLFMKeyCodeSemicolon;
        case Key::Equal:
            return GLFMKeyCodeEqual;
        case Key::LeftBracket:
            return GLFMKeyCodeBracketLeft;
        case Key::RightBracket:
            return GLFMKeyCodeBracketRight;
        case Key::Grave:
            return GLFMKeyCodeBackquote;
        case Key::Escape:
            return GLFMKeyCodeEscape;
        case Key::Enter:
            return GLFMKeyCodeEnter;
        case Key::Tab:
            return GLFMKeyCodeTab;
        case Key::Backspace:
            return GLFMKeyCodeBackspace;
        case Key::Insert:
            return GLFMKeyCodeInsert;
        case Key::Delete:
            return GLFMKeyCodeDelete;
        case Key::Left:
            return GLFMKeyCodeArrowLeft;
        case Key::Right:
            return GLFMKeyCodeArrowRight;
        case Key::Up:
            return GLFMKeyCodeArrowUp;
        case Key::Down:
            return GLFMKeyCodeArrowDown;
        case Key::PageUp:
            return GLFMKeyCodePageUp;
        case Key::PageDown:
            return GLFMKeyCodePageDown;
        case Key::Home:
            return GLFMKeyCodeHome;
        case Key::End:
            return GLFMKeyCodeEnd;
        case Key::CapsLock:
            return GLFMKeyCodeCapsLock;
        case Key::ScrollLock:
            return GLFMKeyCodeScrollLock;
        case Key::NumLock:
            return GLFMKeyCodeNumLock;
        case Key::PrintScreen:
            return GLFMKeyCodePrintScreen;
        case Key::Pause:
            return GLFMKeyCodePause;
        case Key::F1:
            return GLFMKeyCodeF1;
        case Key::F2:
            return GLFMKeyCodeF2;
        case Key::F3:
            return GLFMKeyCodeF3;
        case Key::F4:
            return GLFMKeyCodeF4;
        case Key::F5:
            return GLFMKeyCodeF5;
        case Key::F6:
            return GLFMKeyCodeF6;
        case Key::F7:
            return GLFMKeyCodeF7;
        case Key::F8:
            return GLFMKeyCodeF8;
        case Key::F9:
            return GLFMKeyCodeF9;
        case Key::F10:
            return GLFMKeyCodeF10;
        case Key::F11:
            return GLFMKeyCodeF11;
        case Key::F12:
            return GLFMKeyCodeF12;
        case Key::F13:
            return GLFMKeyCodeF13;
        case Key::F14:
            return GLFMKeyCodeF14;
        case Key::F15:
            return GLFMKeyCodeF15;
        case Key::F16:
            return GLFMKeyCodeF16;
        case Key::F17:
            return GLFMKeyCodeF17;
        case Key::F18:
            return GLFMKeyCodeF18;
        case Key::F19:
            return GLFMKeyCodeF19;
        case Key::F20:
            return GLFMKeyCodeF20;
        case Key::F21:
            return GLFMKeyCodeF21;
        case Key::F22:
            return GLFMKeyCodeF22;
        case Key::F23:
            return GLFMKeyCodeF23;
        case Key::F24:
            return GLFMKeyCodeF24;
        case Key::F25:
            return GLFMKeyCodeUnknown;
        case Key::Numpad0:
            return GLFMKeyCodeNumpad0;
        case Key::Numpad1:
            return GLFMKeyCodeNumpad1;
        case Key::Numpad2:
            return GLFMKeyCodeNumpad2;
        case Key::Numpad3:
            return GLFMKeyCodeNumpad3;
        case Key::Numpad4:
            return GLFMKeyCodeNumpad4;
        case Key::Numpad5:
            return GLFMKeyCodeNumpad5;
        case Key::Numpad6:
            return GLFMKeyCodeNumpad6;
        case Key::Numpad7:
            return GLFMKeyCodeNumpad7;
        case Key::Numpad8:
            return GLFMKeyCodeNumpad8;
        case Key::Numpad9:
            return GLFMKeyCodeNumpad9;
        case Key::NumpadDecimal:
            return GLFMKeyCodeNumpadDecimal;
        case Key::NumpadDivide:
            return GLFMKeyCodeNumpadDivide;
        case Key::NumpadMultiply:
            return GLFMKeyCodeNumpadMultiply;
        case Key::NumpadSubtract:
            return GLFMKeyCodeNumpadSubtract;
        case Key::NumpadAdd:
            return GLFMKeyCodeNumpadAdd;
        case Key::NumpadEnter:
            return GLFMKeyCodeNumpadEnter;
        case Key::NumpadEqual:
            return GLFMKeyCodeNumpadEqual;
        case Key::LeftShift:
            return GLFMKeyCodeShiftLeft;
        case Key::LeftControl:
            return GLFMKeyCodeControlLeft;
        case Key::LeftAlt:
            return GLFMKeyCodeAltLeft;
        case Key::LeftSuper:
            return GLFMKeyCodeMetaLeft;
        case Key::RightShift:
            return GLFMKeyCodeShiftRight;
        case Key::RightControl:
            return GLFMKeyCodeControlRight;
        case Key::RightAlt:
            return GLFMKeyCodeAltRight;
        case Key::RightSuper:
            return GLFMKeyCodeMetaRight;
        case Key::Menu:
            return GLFMKeyCodeMenu;
        default:
            return -1;
    }
}
