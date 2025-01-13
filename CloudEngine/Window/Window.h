#pragma once

#include "CloudEngine/Core.h"

#include <string>

enum class WindowOrientation
{
    All,
    Portrait,
    Landscape,
};

class Window
{
public:
    virtual void Init() = 0;

    virtual bool IsClosing() = 0;

    virtual void PollEvents() = 0;
    virtual void SwapBuffers() = 0;

    virtual void SetOrientationLimits(WindowOrientation orientation) = 0;
    
    /**
     * For internal use only
     */
    virtual void SetData(void *data) {}

    virtual int GetWidth() = 0;
    virtual void SetWidth(int newWidth) = 0;
    virtual int GetHeight() = 0;
    virtual void SetHeight(int newHeight) = 0;

    virtual const std::string &GetTitle() = 0;
    virtual void SetTitle(std::string newTitle) = 0;

    virtual int GetFramebufferWidth() = 0;
    virtual int GetFramebufferHeight() = 0;

    static Ref<Window> Create();

private:
    // static void SetWindowSizeCallback(GLFWwindow *window, int width, int height);
};
