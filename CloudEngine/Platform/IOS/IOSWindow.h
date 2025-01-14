#pragma once

#include "CloudEngine/Window/Window.h"

#include <glfm.h>
#include <string>

class IOSWindow : public Window
{
public:
    ~IOSWindow();

    virtual void Init() override;

    virtual bool IsClosing() override;

    virtual void PollEvents() override;
    virtual void SwapBuffers() override;

    virtual void SetOrientationLimits(WindowOrientation orientation) override;

    virtual CursorMode GetCursorMode() override {}
    virtual void SetCursorMode(CursorMode mode) override {}

    virtual void SetData(void *data) override;

    virtual int GetWidth() override;
    virtual void SetWidth(int newWidth) override;
    virtual int GetHeight() override;
    virtual void SetHeight(int newHeight) override;

    virtual const std::string &GetTitle() override;
    virtual void SetTitle(std::string newTitle) override;

    virtual int GetFramebufferWidth() override;
    virtual int GetFramebufferHeight() override;

private:
    GLFMDisplay *m_Display;
    int m_Width;
    int m_Height;
    std::string m_Title;
};
