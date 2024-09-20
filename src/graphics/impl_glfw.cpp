#include "CloudEngine/renderer.h"
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

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        printf("Failed to initialize OpenGL context\n");
        return;
    }
}

void Window::Update() { glfwSwapBuffers(window); }

void Window::Close()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::Poll() { glfwPollEvents(); }

bool Window::IsClosing() { return glfwWindowShouldClose(window); }
