#import "CloudEngine/Application.h"
#import "CloudEngine/Renderer/Renderer.h"
#import "CloudEngine/Renderer/RendererAPI.h"
#import "CloudEngine/Renderer/Mesh.h"
#import "CloudEngine/Renderer/VertexBuffer.h"
#import "CloudEngine/Renderer/Shader.h"
#import "CloudEngine/Scene/Scene.h"
#import "CloudEngine/Scene/Entity.h"
#import "CloudEngine/Scene/Components.h"
#import "CloudEngine/Input.h"

#import <glfm.h>

static Application *app;

static void update(GLFMDisplay *display, double delta);
static void draw(GLFMDisplay *display);
static void destroy(GLFMDisplay *display);

static void draw(GLFMDisplay *display)
{
    Renderer::Init();

    app->Init();

    int width, height;
    glfmGetDisplaySize(display, &width, &height);
    Renderer::SetViewport(0, 0, width, height);

    Input::Update();

    app->GetMainWindow()->SetWidth(width);
    app->GetMainWindow()->SetHeight(height);

    Renderer::Clear();

    app->Update();
    app->Render();

    glfmSwapBuffers(display);

    Input::UpdateEnd();
}

static void destroy(GLFMDisplay *display)
{
}

static Key ConvertKey(GLFMKeyCode key);

static bool onKey(GLFMDisplay *display, GLFMKeyCode keyCode, GLFMKeyAction action, int modifiers)
{
    Input::KeyCallback(ConvertKey(keyCode), -1, action, modifiers);
}

static TouchPhase ConvertTouchPhase(GLFMTouchPhase phase)
{
    switch (phase)
    {
    case GLFMTouchPhaseBegan:
        return TouchPhase::Begin;
    case GLFMTouchPhaseEnded:
        return TouchPhase::End;
    case GLFMTouchPhaseHover:
        return TouchPhase::Hover;
    case GLFMTouchPhaseMoved:
        return TouchPhase::Move;
    case GLFMTouchPhaseCancelled:
        return TouchPhase::Cancel;
    }
}

static bool onTouch(GLFMDisplay *display, int touch, GLFMTouchPhase phase, double x, double y)
{
    Input::TouchCallback(touch, ConvertTouchPhase(phase), x, y);
}

void glfmMain(GLFMDisplay *display)
{
    glfmSetDisplayConfig(display,
                         GLFMRenderingAPIOpenGLES2,
                         GLFMColorFormatRGBA8888,
                         GLFMDepthFormatNone,
                         GLFMStencilFormatNone,
                         GLFMMultisampleNone);

    app = CreateApplication();
    app->GetMainWindow()->SetData(display);

    glfmSetRenderFunc(display, draw);
    glfmSetSurfaceDestroyedFunc(display, destroy);
    glfmSetMultitouchEnabled(display, true);

    glfmSetKeyFunc(display, onKey);
    glfmSetTouchFunc(display, onTouch);
}

static Key ConvertKey(GLFMKeyCode key)
{
    switch (key)
    {
    case GLFMKeyCodeA:
        return Key::A;
    case GLFMKeyCodeB:
        return Key::B;
    case GLFMKeyCodeC:
        return Key::C;
    case GLFMKeyCodeD:
        return Key::D;
    case GLFMKeyCodeE:
        return Key::E;
    case GLFMKeyCodeF:
        return Key::F;
    case GLFMKeyCodeG:
        return Key::G;
    case GLFMKeyCodeH:
        return Key::H;
    case GLFMKeyCodeI:
        return Key::I;
    case GLFMKeyCodeJ:
        return Key::J;
    case GLFMKeyCodeK:
        return Key::K;
    case GLFMKeyCodeL:
        return Key::L;
    case GLFMKeyCodeM:
        return Key::M;
    case GLFMKeyCodeN:
        return Key::N;
    case GLFMKeyCodeO:
        return Key::O;
    case GLFMKeyCodeP:
        return Key::P;
    case GLFMKeyCodeQ:
        return Key::Q;
    case GLFMKeyCodeR:
        return Key::R;
    case GLFMKeyCodeS:
        return Key::S;
    case GLFMKeyCodeT:
        return Key::T;
    case GLFMKeyCodeU:
        return Key::U;
    case GLFMKeyCodeV:
        return Key::V;
    case GLFMKeyCodeW:
        return Key::W;
    case GLFMKeyCodeX:
        return Key::X;
    case GLFMKeyCodeY:
        return Key::Y;
    case GLFMKeyCodeZ:
        return Key::Z;
    case GLFMKeyCode0:
        return Key::Zero;
    case GLFMKeyCode1:
        return Key::One;
    case GLFMKeyCode2:
        return Key::Two;
    case GLFMKeyCode3:
        return Key::Three;
    case GLFMKeyCode4:
        return Key::Four;
    case GLFMKeyCode5:
        return Key::Five;
    case GLFMKeyCode6:
        return Key::Six;
    case GLFMKeyCode7:
        return Key::Seven;
    case GLFMKeyCode8:
        return Key::Eight;
    case GLFMKeyCode9:
        return Key::Nine;
    case GLFMKeyCodeSpace:
        return Key::Space;
        // case GLFMKeyCodeApostrophe:
        // return Key::Apostrophe;
    case GLFMKeyCodeComma:
        return Key::Comma;
    case GLFMKeyCodeMinus:
        return Key::Minus;
    case GLFMKeyCodePeriod:
        return Key::Period;
    case GLFMKeyCodeSlash:
        return Key::Slash;
    case GLFMKeyCodeSemicolon:
        return Key::Semicolon;
    case GLFMKeyCodeEqual:
        return Key::Equal;
    case GLFMKeyCodeBracketLeft:
        return Key::LeftBracket;
    case GLFMKeyCodeBracketRight:
        return Key::RightBracket;
    case GLFMKeyCodeBackquote:
        return Key::Grave;
    case GLFMKeyCodeEscape:
        return Key::Escape;
    case GLFMKeyCodeEnter:
        return Key::Enter;
    case GLFMKeyCodeTab:
        return Key::Tab;
    case GLFMKeyCodeBackspace:
        return Key::Backspace;
    case GLFMKeyCodeInsert:
        return Key::Insert;
    case GLFMKeyCodeDelete:
        return Key::Delete;
    case GLFMKeyCodeArrowLeft:
        return Key::Left;
    case GLFMKeyCodeArrowRight:
        return Key::Right;
    case GLFMKeyCodeArrowUp:
        return Key::Up;
    case GLFMKeyCodeArrowDown:
        return Key::Down;
    case GLFMKeyCodePageUp:
        return Key::PageUp;
    case GLFMKeyCodePageDown:
        return Key::PageDown;
    case GLFMKeyCodeHome:
        return Key::Home;
    case GLFMKeyCodeEnd:
        return Key::End;
    case GLFMKeyCodeCapsLock:
        return Key::CapsLock;
    case GLFMKeyCodeScrollLock:
        return Key::ScrollLock;
    case GLFMKeyCodeNumLock:
        return Key::NumLock;
    case GLFMKeyCodePrintScreen:
        return Key::PrintScreen;
    case GLFMKeyCodePause:
        return Key::Pause;
    case GLFMKeyCodeF1:
        return Key::F1;
    case GLFMKeyCodeF2:
        return Key::F2;
    case GLFMKeyCodeF3:
        return Key::F3;
    case GLFMKeyCodeF4:
        return Key::F4;
    case GLFMKeyCodeF5:
        return Key::F5;
    case GLFMKeyCodeF6:
        return Key::F6;
    case GLFMKeyCodeF7:
        return Key::F7;
    case GLFMKeyCodeF8:
        return Key::F8;
    case GLFMKeyCodeF9:
        return Key::F9;
    case GLFMKeyCodeF10:
        return Key::F10;
    case GLFMKeyCodeF11:
        return Key::F11;
    case GLFMKeyCodeF12:
        return Key::F12;
    case GLFMKeyCodeF13:
        return Key::F13;
    case GLFMKeyCodeF14:
        return Key::F14;
    case GLFMKeyCodeF15:
        return Key::F15;
    case GLFMKeyCodeF16:
        return Key::F16;
    case GLFMKeyCodeF17:
        return Key::F17;
    case GLFMKeyCodeF18:
        return Key::F18;
    case GLFMKeyCodeF19:
        return Key::F19;
    case GLFMKeyCodeF20:
        return Key::F20;
    case GLFMKeyCodeF21:
        return Key::F21;
    case GLFMKeyCodeF22:
        return Key::F22;
    case GLFMKeyCodeF23:
        return Key::F23;
    case GLFMKeyCodeF24:
        return Key::F24;
    case GLFMKeyCodeNumpad0:
        return Key::Numpad0;
    case GLFMKeyCodeNumpad1:
        return Key::Numpad1;
    case GLFMKeyCodeNumpad2:
        return Key::Numpad2;
    case GLFMKeyCodeNumpad3:
        return Key::Numpad3;
    case GLFMKeyCodeNumpad4:
        return Key::Numpad4;
    case GLFMKeyCodeNumpad5:
        return Key::Numpad5;
    case GLFMKeyCodeNumpad6:
        return Key::Numpad6;
    case GLFMKeyCodeNumpad7:
        return Key::Numpad7;
    case GLFMKeyCodeNumpad8:
        return Key::Numpad8;
    case GLFMKeyCodeNumpad9:
        return Key::Numpad9;
    case GLFMKeyCodeNumpadDecimal:
        return Key::NumpadDecimal;
    case GLFMKeyCodeNumpadDivide:
        return Key::NumpadDivide;
    case GLFMKeyCodeNumpadMultiply:
        return Key::NumpadMultiply;
    case GLFMKeyCodeNumpadSubtract:
        return Key::NumpadSubtract;
    case GLFMKeyCodeNumpadAdd:
        return Key::NumpadAdd;
    case GLFMKeyCodeNumpadEnter:
        return Key::NumpadEnter;
    case GLFMKeyCodeNumpadEqual:
        return Key::NumpadEqual;
    case GLFMKeyCodeShiftLeft:
        return Key::LeftShift;
    case GLFMKeyCodeControlLeft:
        return Key::LeftControl;
    case GLFMKeyCodeAltLeft:
        return Key::LeftAlt;
    case GLFMKeyCodeMetaLeft:
        return Key::LeftSuper;
    case GLFMKeyCodeShiftRight:
        return Key::RightShift;
    case GLFMKeyCodeControlRight:
        return Key::RightControl;
    case GLFMKeyCodeAltRight:
        return Key::RightAlt;
    case GLFMKeyCodeMetaRight:
        return Key::RightSuper;
    case GLFMKeyCodeMenu:
        return Key::Menu;
    default:
        return Key::None;
    }
}
