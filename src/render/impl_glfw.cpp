#include "CloudEngine/renderer.h"
#include "CloudEngine/window.h"

#include <GLFW/glfw3.h>
#include <cstdio>

GLFWwindow *window;

void Renderer::Init()
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return;
    }
}

void Renderer::Update() {}

void Renderer::Destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::Init()
{
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("Failed to initialize GLFW window\n");
        return;
    }

    glfwMakeContextCurrent(window);
}

void Window::Update() { glfwSwapBuffers(window); }

void Window::Poll() { glfwPollEvents(); }

bool Window::IsClosing() { return glfwWindowShouldClose(window); }
