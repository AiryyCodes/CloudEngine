#include "CloudEngine/Window/Window.h"
#include "CloudEngine/Renderer/Renderer.h"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

Window::~Window()
{
    glfwDestroyWindow(m_GLFWWindow);
}

void Window::Init()
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

#ifdef __APPLE__
    chdir("../");

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwDefaultWindowHints();

    /* We need to explicitly ask for a 3.2 context on OS X */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Width = 1280;
    m_Height = 720;
    m_GLFWWindow = glfwCreateWindow(1280, 720, "Cloud Engine", NULL, NULL);
    if (!m_GLFWWindow)
    {
        printf("Failed to initialize GLFW window\n");
        return;
    }

    glfwSetWindowUserPointer(m_GLFWWindow, static_cast<void *>(this));

    glfwSetWindowSizeCallback(m_GLFWWindow, [](GLFWwindow *window, int width, int height)
                              { auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
                                self->SetWidth(width);
                                self->SetHeight(height); });

    glfwSetFramebufferSizeCallback(m_GLFWWindow, [](GLFWwindow *window, int width, int height)
                                   { Renderer::SetViewport(0, 0, width, height); });

    glfwMakeContextCurrent(m_GLFWWindow);
    glfwSwapInterval(0);
}

bool Window::IsClosing()
{
    return glfwWindowShouldClose(m_GLFWWindow);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_GLFWWindow);
}

int Window::GetWidth()
{
    return m_Width;
}

void Window::SetWidth(int newWidth)
{
    m_Width = newWidth;
    glfwSetWindowSize(m_GLFWWindow, m_Width, m_Height);
}

int Window::GetHeight()
{
    return m_Height;
}

void Window::SetHeight(int newHeight)
{
    m_Height = newHeight;
    glfwSetWindowSize(m_GLFWWindow, m_Width, m_Height);
}

int Window::GetFramebufferWidth()
{
    int width;
    int height;
    glfwGetFramebufferSize(m_GLFWWindow, &width, &height);
    return width;
}

int Window::GetFramebufferHeight()
{
    int width;
    int height;
    glfwGetFramebufferSize(m_GLFWWindow, &width, &height);
    return height;
}