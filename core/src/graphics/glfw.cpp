#include "CloudEngine/entry.h"
#include "CloudEngine/input.h"
#include "CloudEngine/logger.h"
#include "CloudEngine/time.h"
#include "CloudEngine/graphics/window.h"

#include <GLFW/glfw3.h>
#include <cstdio>

GLFWwindow *window;

void Window::Init()
{
    if (!glfwInit())
    {
        LOG_ERROR("Failed to initialize GLFW");
        return;
    }

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        LOG_ERROR("Failed to initialize GLFW window");
        return;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int xScale, int yScale)
                                   { Application::Get().GetRenderer().ResizeViewport(xScale, yScale); });

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       { Input::OnKeyHandler(key, scancode, action, mods); });

    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos)
                             { Input::OnMousePosHandler((float)xPos, (float)yPos); });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
                               { Input::OnMouseButtonHandler(button, action, mods); });

    glfwMakeContextCurrent(window);
}

void Window::Update()
{
    glfwSwapBuffers(window);
    glfwGetWindowSize(window, &width, &height);
}

void Window::Close()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::Poll() { glfwPollEvents(); }

bool Window::IsClosing() { return glfwWindowShouldClose(window); }

void Window::SetWidth(int width)
{
    this->width = width;
    glfwSetWindowSize(window, width, height);
}

void Window::SetHeight(int height)
{
    this->height = height;
    glfwSetWindowSize(window, width, height);
}

void Window::SetTitle(std::string title)
{
    glfwSetWindowTitle(window, title.c_str());
}

GLFWwindow *Window::GetGLFWWindow()
{
    return window;
}

void Input::SetCursorMode(int mode)
{
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}

void Input::ToggleCursor()
{
    int currMode = glfwGetInputMode(window, GLFW_CURSOR);
    glfwSetInputMode(window, GLFW_CURSOR, currMode == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool Input::IsCursorLocked()
{
    return glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void Time::Update()
{
    float currentFrame = glfwGetTime();
    delta = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
