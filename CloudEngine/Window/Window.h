#pragma once

struct GLFWwindow;
class Window
{
public:
    void Init();

    bool IsClosing();

    void PollEvents();
    void SwapBuffers();

    int GetWidth();
    void SetWidth(int newWidth);
    int GetHeight();
    void SetHeight(int newHeight);

    int GetFramebufferWidth();
    int GetFramebufferHeight();

private:
    static void SetWindowSizeCallback(GLFWwindow *window, int width, int height);

private:
    GLFWwindow *m_GLFWWindow;
    int m_Width;
    int m_Height;
};