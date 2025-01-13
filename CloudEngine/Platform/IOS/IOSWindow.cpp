#include "CloudEngine/Platform/IOS/IOSWindow.h"
#include "CloudEngine/Core.h"
#include "CloudEngine/Window/Window.h"
#include "glfm.h"

#include <cassert>
#include <string>
#include <unistd.h>

Ref<Window> Window::Create()
{
    return CreateRef<IOSWindow>();
}

IOSWindow::~IOSWindow()
{
}

void IOSWindow::Init()
{
}

bool IOSWindow::IsClosing()
{
    return false;
}

void IOSWindow::PollEvents()
{
}

void IOSWindow::SwapBuffers()
{
}

void IOSWindow::SetData(void *data)
{
    assert(static_cast<GLFMDisplay *>(data) && "IOSWindow::SetData() param is not of type GLFMDisplay*");
    m_Display = static_cast<GLFMDisplay *>(data);
}

void IOSWindow::SetOrientationLimits(WindowOrientation orientation)
{
    GLFMInterfaceOrientation glfmOrientation;
    switch (orientation)
    {
        case WindowOrientation::All:
            glfmOrientation = GLFMInterfaceOrientationAll;
            break;
        case WindowOrientation::Portrait:
            glfmOrientation = GLFMInterfaceOrientationPortrait;
            break;
        case WindowOrientation::Landscape:
            glfmOrientation = GLFMInterfaceOrientationLandscape;
            break;
        default:
            glfmOrientation = GLFMInterfaceOrientationAll;
            break;
    }
    
    glfmSetSupportedInterfaceOrientation(m_Display, glfmOrientation);
}

int IOSWindow::GetWidth()
{
    return m_Width;
}

void IOSWindow::SetWidth(int newWidth)
{
    m_Width = newWidth;
}

int IOSWindow::GetHeight()
{
    return m_Height;
}

void IOSWindow::SetHeight(int newHeight)
{
    m_Height = newHeight;
}

const std::string &IOSWindow::GetTitle()
{
    return m_Title;
}

void IOSWindow::SetTitle(std::string newTitle)
{
    m_Title = newTitle;
}

int IOSWindow::GetFramebufferWidth()
{
    int width;
    int height;
    return width;
}

int IOSWindow::GetFramebufferHeight()
{
    int width;
    int height;
    return height;
}
