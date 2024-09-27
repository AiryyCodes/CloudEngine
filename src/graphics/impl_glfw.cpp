#include "CloudEngine/input.h"
#include "CloudEngine/time.h"
#include "CloudEngine/window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>

GLFWwindow *window;

void Window::Init()
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return;
    }

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("Failed to initialize GLFW window\n");
        return;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int xScale, int yScale)
                                   { glViewport(0, 0, xScale, yScale); });

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       { Input::OnKeyHandler(key, scancode, action, mods); });

    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos)
                             { Input::OnMousePosHandler((float)xPos, (float)yPos); });

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        printf("Failed to initialize OpenGL context\n");
        return;
    }
}

void Window::Update()
{
    glfwSwapBuffers(window);
    glfwGetFramebufferSize(window, &width, &height);
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
