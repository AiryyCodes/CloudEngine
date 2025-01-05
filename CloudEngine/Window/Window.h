#pragma once

#include <string>
struct GLFWwindow;
class Window
{
public:
    ~Window();

    void Init();

    bool IsClosing();

    void PollEvents();
    void SwapBuffers();

    int GetWidth() { return m_Width; }
    void SetWidth(int newWidth);
    int GetHeight() { return m_Height; }
    void SetHeight(int newHeight);

    const std::string &GetTitle() { return m_Title; }
    void SetTitle(std::string newTitle);

    int GetFramebufferWidth();
    int GetFramebufferHeight();

private:
    static void SetWindowSizeCallback(GLFWwindow *window, int width, int height);

private:
    GLFWwindow *m_GLFWWindow;
    int m_Width;
    int m_Height;
    std::string m_Title;
};