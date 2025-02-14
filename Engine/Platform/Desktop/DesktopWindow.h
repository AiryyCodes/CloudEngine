#pragma once

#include "Engine/Input.h"
#include "Engine/Window/Window.h"

struct GLFWwindow;
class DesktopWindow : public Window
{
public:
    ~DesktopWindow();

    virtual void Init() override;

    virtual bool IsClosing() override;

    virtual void PollEvents() override;
    virtual void SwapBuffers() override;

    virtual void SetOrientationLimits(WindowOrientation orientation) override;

    virtual CursorMode GetCursorMode() override;
    virtual void SetCursorMode(CursorMode mode) override;

    virtual int GetWidth() override;
    virtual void SetWidth(int newWidth) override;
    virtual int GetHeight() override;
    virtual void SetHeight(int newHeight) override;

    virtual const std::string &GetTitle() override;
    virtual void SetTitle(std::string newTitle) override;

    virtual int GetFramebufferWidth() override;
    virtual int GetFramebufferHeight() override;

private:
    GLFWwindow *m_GLFWWindow;
    int m_Width;
    int m_Height;
    std::string m_Title;
};